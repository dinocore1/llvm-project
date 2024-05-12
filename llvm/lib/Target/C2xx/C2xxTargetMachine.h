#ifndef LLVM_LIB_TARGET_C2XX_C2XXTARGETMACHINE_H
#define LLVM_LIB_TARGET_C2XX_C2XXTARGETMACHINE_H

#include "C2xxSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>


namespace llvm {
class StringRef;

/// C2xxTargetMachine
///
class C2xxTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  C2xxSubtarget Subtarget;

public:
  C2xxTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool JIT);
  ~C2xxTargetMachine() override;

  const C2xxSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  MachineFunctionInfo *
  createMachineFunctionInfo(BumpPtrAllocator &Allocator, const Function &F,
                            const TargetSubtargetInfo *STI) const override;
}; // C2xxTargetMachine.

} // end namespace llvm

#endif // LLVM_LIB_TARGET_C2XX_C2XXTARGETMACHINE_H