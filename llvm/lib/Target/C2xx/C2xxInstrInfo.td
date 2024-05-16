
include "C2xxInstrFormats.td"

def GR32 : RegisterOperand<GP32>;

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
}
