
class C2xxReg<string n, list<Register> subregs = []> : Register<n> {
    let Namespace = "C2xx";
    let SubRegs = subregs;
}

// Subregister indices.
let Namespace = "C2xx" in {
    def sub_16bit       : SubRegIndex<16>;
    def sub_16bit_hi     : SubRegIndex<16, 16>;
}

// 16-bit registers
def ST0 : C2xxReg<"ST0">;
def ST1 : C2xxReg<"ST1">;
def AH  : C2xxReg<"AH">;
def AL  : C2xxReg<"AL">;
def PH  : C2xxReg<"PH">;
def PL  : C2xxReg<"PL">;
def T   : C2xxReg<"T">;
def TL  : C2xxReg<"TL">;
def DP  : C2xxReg<"DP">;
def SP  : C2xxReg<"SP">;
def AR0 : C2xxReg<"AR0">;
def AR1 : C2xxReg<"AR1">;
def AR2 : C2xxReg<"AR2">;
def AR3 : C2xxReg<"AR3">;
def AR4 : C2xxReg<"AR4">;
def AR5 : C2xxReg<"AR5">;
def AR6 : C2xxReg<"AR6">;
def AR7 : C2xxReg<"AR7">;

// 32-bit registers
let SubRegIndices = [sub_16bit, sub_16bit_hi], CoveredBySubRegs = 1 in {
def ACC     : C2xxReg<"ACC", [AL,AH]>;
def P       : C2xxReg<"P", [PL,PH]>;
def XT      : C2xxReg<"XT", [TL, T]>;
}

let SubRegIndices = [sub_16bit], CoveredBySubRegs = 1 in {
foreach i = {0-7} in {
    def XAR#i    : C2xxReg<"XAR"#i, [!cast<C2xxReg>("AR"#i)]>; 
}
}

def STATUS_REG : RegisterClass<"C2xx", [i16], 16, (add ST0, ST1)>;

def ACC_REG : RegisterClass<"C2xx", [i32], 32, (add ACC)>;
def ACC_REG16 : RegisterClass<"C2xx", [i16], 16, (add AH, AL)>;

def PRODUCT_REG : RegisterClass<"C2xx", [i32], 32, (add P)>;
def PRODUCT_REG16: RegisterClass<"C2xx", [i16], 16, (add PH, PL)>;

def MULTIPLICAND_REG : RegisterClass<"C2xx", [i32], 32, (add XT)>;
def MULTIPLICAND_REG16: RegisterClass<"C2xx", [i16], 16, (add T, TL)>;

def DATAPAGE_REG : RegisterClass<"C2xx", [i16], 16, (add DP)>;

def STACKPOINTER_REG : RegisterClass<"C2xx", [i16], 16, (add SP)>;

def GP16 : RegisterClass<"C2xx", [i16], 16, (add AR0, AR1, AR2, AR3, AR4, AR5, AR6, AR7)>;
def GP32 : RegisterClass<"C2xx", [i32], 32, (add XAR0, XAR1, XAR2, XAR3, XAR4, XAR5, XAR6, XAR7)>;


