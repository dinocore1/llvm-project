include "llvm/Target/Target.td"

include "C28xRegisterInfo.td"

def : Processor<"generic", NoItineraries, []>;

def C28x : Target {
}