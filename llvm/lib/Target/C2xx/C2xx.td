include "llvm/Target/Target.td"

include "C2xxRegisterInfo.td"

include "C2xxCallingConv.td"

def : Processor<"generic", NoItineraries, []>;
def : Processor<"c28x", NoItineraries, []>;

include "C2xxInstrInfo.td"

def C2xxInstrInfo : InstrInfo;

def C2xxAsmParser : AsmParser;

def C2xxAsmWriter : AsmWriter {
  string AsmWriterClassName = "InstPrinter";
}

def C2xx : Target {
    let InstructionSet = C2xxInstrInfo;
    let AssemblyParsers = [C2xxAsmParser];
}