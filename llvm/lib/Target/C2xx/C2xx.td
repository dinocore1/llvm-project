include "llvm/Target/Target.td"

include "C2xxRegisterInfo.td"

def : Processor<"generic", NoItineraries, []>;

def C2xx : Target {
}