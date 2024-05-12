
class C2xxReg<string n, list<Register> subregs = []> : Register<n> {
    let Namespace = "C2xx";
    let SubRegs = subregs;
}

def sub_16bit : SubRegIndex<16, 16>;
def sub_16bit_hi : SubRegIndex<16>;

// Accumulator
def AH  : C2xxReg<"AH">;
def AL  : C2xxReg<"AL">;
let SubRegIndices = [sub_16bit_hi, sub_16bit] in {
    def ACC : C2xxReg<"ACC", [AH, AL]>;
}

def ACC_s : RegisterClass<"C2xx", [i16], 16, (add AH, AL)>;
def ACC_c : RegisterClass<"C2xx", [i32], 32, (add ACC)>;

