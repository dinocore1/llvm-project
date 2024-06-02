#include "C2xx.h"
#include "C2xxRegisterInfo.h"
#include "MCTargetDesc/C2xxMCTargetDesc.h"
#include "TargetInfo/C2xxTargetInfo.h"

#include "llvm/ADT/APInt.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/TargetRegistry.h"


#define DEBUG_TYPE "c2xx-asm-parser"

using namespace llvm;

namespace {

class C2xxAsmParser : public MCTargetAsmParser {
    const MCSubtargetInfo &STI;
    MCAsmParser &Parser;

    bool ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;
    
    bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;

    ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                               SMLoc &EndLoc) override;

    bool ParseOperand(OperandVector &Operands);

    bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

    #define GET_ASSEMBLER_HEADER
    #include "C2xxGenAsmMatcher.inc"

public:
    C2xxAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                    const MCInstrInfo &MII, const MCTargetOptions &Options)
        : MCTargetAsmParser(Options, STI, MII),
        STI(STI),
        Parser(Parser) {
        MCAsmParserExtension::Initialize(Parser);
        // MRI = getContext().getRegisterInfo();

        setAvailableFeatures(ComputeAvailableFeatures(STI.getFeatureBits()));
    }

    
};

class C2xxOperand : public MCParsedAsmOperand {
    enum OperandKind {
        OpKind_Token,
        OpKind_Reg,
        OpKind_Imm,
        OpKind_Mem,
    } Kind;

    union {
        StringRef Tok;
        unsigned Reg;
        const MCExpr *Imm;
    };

    SMLoc StartLoc, EndLoc;

public:
    C2xxOperand(OperandKind Kind, SMLoc const &StartLoc, SMLoc const &EndLoc)
     : Kind(Kind), StartLoc(StartLoc), EndLoc(EndLoc) {}
    
    SMLoc getStartLoc() const override { return StartLoc; }
    SMLoc getEndLoc() const override { return EndLoc; }

    bool isToken() const override { return Kind == OpKind_Token; }
    bool isReg() const override { return Kind == OpKind_Reg; }
    bool isImm()   const override { return Kind == OpKind_Imm; }
    bool isMem() const override { return Kind == OpKind_Mem; }

    bool isUImm7() {
        if (!isImm())
            return false;
        
        if (const auto *ConstExpr = dyn_cast<MCConstantExpr>(Imm)) {
            int64_t Value = ConstExpr->getValue();
            return isUInt<7>(Value);
        }
        return false;
    }

    StringRef getToken() const {
        assert(Kind == OpKind_Token && "Invalid access!");
        return Tok;
    }

    MCRegister getReg() const override {
        assert(Kind == OpKind_Reg && "Invalid access!");
        return Reg;
    }

    const MCExpr* getImm() const {
        assert(Kind == OpKind_Imm && "Invalid access!");
        return Imm;
    }

    static std::unique_ptr<C2xxOperand> CreateToken(StringRef Str, SMLoc S) {
        auto Token = std::make_unique<C2xxOperand>(OpKind_Token, S, S);
        Token->Tok = Str;
        return Token;
    }

    static std::unique_ptr<C2xxOperand> CreateReg(unsigned RegNum, SMLoc S, SMLoc E) {
        auto Reg = std::make_unique<C2xxOperand>(OpKind_Reg, S, E);
        Reg->Reg = RegNum;
        return Reg;
    }

    static std::unique_ptr<C2xxOperand> CreateImm(const MCExpr *Val, SMLoc S, SMLoc E) {
        auto Imm = std::make_unique<C2xxOperand>(OpKind_Imm, S, E);
        Imm->Imm = Val;
        return Imm;
    }

    void addExpr(MCInst &Inst, const MCExpr *Expr) const {
        // Add as immediate when possible.  Null MCExpr = 0.
        if (!Expr)
            Inst.addOperand(MCOperand::createImm(0));
        else if (const auto *CE = dyn_cast<MCConstantExpr>(Expr))
            Inst.addOperand(MCOperand::createImm(CE->getValue()));
        else
            Inst.addOperand(MCOperand::createExpr(Expr));
    }

    void addRegOperands(MCInst &Inst, unsigned N) const {
        assert(N == 1 && "Invalid number of operands!");
        Inst.addOperand(MCOperand::createReg(getReg()));
    }

    void addImmOperands(MCInst &Inst, unsigned N) const {
        assert(N == 1 && "Invalid number of operands!");
        const MCExpr *Expr = getImm();
        addExpr(Inst, Expr);
    }

    void addUImm7Operands(MCInst &Inst, unsigned N) const {
        addImmOperands(Inst, N);
    }

    void print(raw_ostream &O) const override {
        switch (Kind) {
            case OpKind_Token:
                O << "Token " << Tok;
                break;
            case OpKind_Reg:
                O << "Register " << Reg;
                break;
            case OpKind_Imm:
                O << "Immediate " << *Imm;
                break;
            // TODO: handle memory
            default:
                llvm_unreachable("unknown OpKind");
        }
    }
    
};

} // end anonymous namespace

// Auto-generated by TableGen
static MCRegister MatchRegisterName(StringRef Name);
// static MCRegister MatchRegisterAltName(StringRef Name);

bool C2xxAsmParser::ParseInstruction(ParseInstructionInfo &Info,
                                       StringRef Name, SMLoc NameLoc,
                                       OperandVector &Operands) {

  // First operand is the instruction mnemonic
  Operands.push_back(C2xxOperand::CreateToken(Name, NameLoc));

  if (getLexer().is(AsmToken::EndOfStatement))
    return false;

  // Parse first operand
  if (ParseOperand(Operands))
    return true;

  // Parse second operand if any
  if (parseOptionalToken(AsmToken::Comma) && ParseOperand(Operands))
    return true;

  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    SMLoc Loc = getLexer().getLoc();
    getParser().eatToEndOfStatement();
    return Error(Loc, "unexpected token");
  }

  // Consume the EndOfStatement
  getParser().Lex();
  return false;
}

bool C2xxAsmParser::ParseOperand(OperandVector &Operands) {
    switch (getLexer().getKind()) {
        default: return true;
        case AsmToken::Identifier: {
            MCRegister RegNo;
            SMLoc StartLoc, EndLoc;
            if (!parseRegister(RegNo, StartLoc, EndLoc)) {
                Operands.push_back(C2xxOperand::CreateReg(RegNo, StartLoc, EndLoc));
                return false;
            }
            [[fallthrough]];
        }

        case AsmToken::Hash:
            SMLoc StartLoc = getParser().getTok().getLoc();
            // Eat '#'
            getLexer().Lex();
            const MCExpr *Val;
            if (!getParser().parseExpression(Val)) {
                SMLoc EndLoc = getParser().getTok().getLoc();
                Operands.push_back(C2xxOperand::CreateImm(Val, StartLoc, EndLoc));
                return false;
            }
            return true;
    }
}

bool C2xxAsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) {
  ParseStatus Res = tryParseRegister(Reg, StartLoc, EndLoc);
  if (Res.isFailure())
    return Error(StartLoc, "invalid register name");
  if (Res.isSuccess())
    return false;
  if (Res.isNoMatch())
    return true;

  llvm_unreachable("unknown parse status");
}

ParseStatus C2xxAsmParser::tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                                              SMLoc &EndLoc) {
  if (getLexer().getKind() == AsmToken::Identifier) {
    auto Name = getLexer().getTok().getIdentifier().upper();
    Reg = MatchRegisterName(Name);
    if (Reg == C2xx::NoRegister) {
    //   Reg = MatchRegisterAltName(Name);
    //   if (Reg == C2xx::NoRegister)
    //     return ParseStatus::NoMatch;
        return ParseStatus::NoMatch;
    }

    AsmToken const &T = getParser().getTok();
    StartLoc = T.getLoc();
    EndLoc = T.getEndLoc();
    getLexer().Lex(); // eat register token

    return ParseStatus::Success;
  }

  return ParseStatus::Failure;
}

bool C2xxAsmParser::MatchAndEmitInstruction(SMLoc Loc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) {


  MCInst Inst;
  unsigned MatchResult = MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm);

  switch (MatchResult) {
    case Match_Success:
        Inst.setLoc(Loc);
        Out.emitInstruction(Inst, STI);
        return false;
    case Match_MnemonicFail:
        return Error(Loc, "invalid instruction mnemonic");
    case Match_InvalidOperand: {
        SMLoc ErrorLoc = Loc;
        if (ErrorInfo != ~0U) {
        if (ErrorInfo >= Operands.size())
            return Error(ErrorLoc, "too few operands for instruction");

        ErrorLoc = ((C2xxOperand &)*Operands[ErrorInfo]).getStartLoc();
        if (ErrorLoc == SMLoc())
            ErrorLoc = Loc;
        }
        return Error(ErrorLoc, "invalid operand for instruction");
    }
    default:
        return true;

  }

}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeC2xxAsmParser() {
  RegisterMCAsmParser<C2xxAsmParser> X(getTheC2xxTarget());
}

#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "C2xxGenAsmMatcher.inc"