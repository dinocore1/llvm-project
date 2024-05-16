
class C2xxInst<dag outs, dag ins, string asmstr> : Instruction {
    field bits<16> Inst;
    
    let Namespace = "C2xx";

    let OutOperandList = outs;
    let InOperandList = ins;

    let AsmString = asmstr;
}

