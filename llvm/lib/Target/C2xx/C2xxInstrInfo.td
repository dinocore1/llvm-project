
include "C2xxInstrFormats.td"

def ABORTI : C2xxInst<(outs), (ins), "ABORTI"> {
    let Inst{15-0} = 0x0001;
}

let Uses = [SP] in {
def PUSHACC : C2xxInst<(outs), (ins), "PUSH ACC"> {
    let Inst{15-0} = 0b0001111010111101;
}
}
