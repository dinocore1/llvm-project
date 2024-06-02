#include "MCTargetDesc/C2xxMCTargetDesc.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"
STATISTIC(MCNumEmitted, "Number of MC instructions emitted");


namespace {

class C2xxMCCodeEmitter : public MCCodeEmitter {
    const MCInstrInfo &MCII;
    MCContext &Ctx;

public:
    C2xxMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx)
        : MCII(MCII), Ctx(Ctx) {}
    
    ~C2xxMCCodeEmitter() override = default;

    void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
    
    /// getMachineOpValue - Return binary encoding of operand. If the machine
    /// operand requires relocation, record the relocation and return zero.
    unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                SmallVectorImpl<MCFixup> &Fixups,
                                const MCSubtargetInfo &STI) const;

    // getBinaryCodeForInstr - TableGen'erated function for getting the
    // binary encoding for an instruction.
    uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                    SmallVectorImpl<MCFixup> &Fixups,
                                    const MCSubtargetInfo &STI) const;

};

}

unsigned C2xxMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                SmallVectorImpl<MCFixup> &Fixups,
                                const MCSubtargetInfo &STI) const {

    if (MO.isReg()) {
        return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());
    }
    if (MO.isImm()) {
        return static_cast<unsigned>(MO.getImm());
    }

    return 0;
}

void C2xxMCCodeEmitter::encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const {

    uint64_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);
    ++MCNumEmitted;
    support::endian::write<uint32_t>(CB, Bits, llvm::endianness::big);
}

#include "C2xxGenMCCodeEmitter.inc"

MCCodeEmitter *llvm::createC2xxMCCodeEmitter(const MCInstrInfo &MCII,
                                                MCContext &Ctx) {
  return new C2xxMCCodeEmitter(MCII, Ctx);
}
