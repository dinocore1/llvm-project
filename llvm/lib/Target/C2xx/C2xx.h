#ifndef LLVM_LIB_TARGET_C2XX_C2XX_H
#define LLVM_LIB_TARGET_C2XX_C2XX_H

// #include "MCTargetDesc/C2xxMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace C2xxCC {
  // C2xx specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,
    COND_N  = 6,  // jump if negative
    COND_NONE,    // unconditional

    COND_INVALID = -1
  };
}

namespace llvm {
class FunctionPass;
class C2xxTargetMachine;
class PassRegistry;

FunctionPass *createC2xxISelDag(C2xxTargetMachine &TM,
                                  CodeGenOptLevel OptLevel);

void initializeC2xxDAGToDAGISelPass(PassRegistry &);

} // namespace llvm

#endif
