#include "C2xxSubtarget.h"
#include "C2xx.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "C2xx-subtarget"



#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "C2xxGenSubtargetInfo.inc"

void C2xxSubtarget::anchor() { }

C2xxSubtarget &
C2xxSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS) {
  ExtendedInsts = false;
  HWMultMode = NoHWMult;

  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "C2xx";

  ParseSubtargetFeatures(CPUName, CPUName, FS);

  return *this;
}

C2xxSubtarget::C2xxSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : C2xxGenSubtargetInfo(TT, CPU, CPU, FS),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this),
      FrameLowering(*this) {}
