
include "C2xxInstrFormats.td"

def GR32 : RegisterOperand<GP32>;

// uimm7 predicate - True if the immediate is in the range [0, 127].
def UImm7Operand : AsmOperandClass {
  let Name = "UImm6";
  let DiagnosticType = "InvalidImm0_127";
}

def i7imm : Operand<i8>, ImmLeaf<i8, [{ return Imm >=0 && Imm < 128; }]> {
    let ParserMatchClass = UImm7Operand;
    let DecoderMethod = "DecodeUImm<7>";
}

def ABORTI : C2xxInst<(outs), (ins), "ABORTI"> {
    let Inst{15-0} = 0x0001;
}

let Uses = [SP] in {
def pushACC : C2xxInst<(outs), (ins RegisterOperand<ACC_REG32>:$acc), "PUSH ACC"> {
    let Inst{15-0} = 0b0001111010111101;
}

def pushXT : C2xxInst<(outs), (ins RegisterOperand<XT_REG32>:$xt), "PUSH XT"> {
    let Inst{15-0} = 0b1010101110111101;
}

def addSP : C2xxInst<(outs), (ins i7imm:$imm), "ADDB SP, $imm"> {
    bits<7> imm;
    let Inst{15-7} = 0b111111100;
    let Inst{6-0} = imm;
}
}
