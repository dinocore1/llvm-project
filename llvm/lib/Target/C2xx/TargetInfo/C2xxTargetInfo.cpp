#include "TargetInfo/C2xxTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheC2xxTarget() {
  static Target TheC2xxTarget;
  return TheC2xxTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeC2xxTargetInfo() {
  RegisterTarget<Triple::c2xx> X(getTheC2xxTarget(), "c2xx",
                                   "C2xx [experimental]", "C2xx");
}