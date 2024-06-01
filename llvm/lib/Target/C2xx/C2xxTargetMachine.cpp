#include "C2xxTargetMachine.h"
#include "C2xx.h"
#include "C2xxMachineFunctionInfo.h"
#include "TargetInfo/C2xxTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>
using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeC2xxTarget() {
  // Register the target.
  // RegisterTargetMachine<C2xxTargetMachine> X(getTheC2xxTarget());
  // PassRegistry &PR = *PassRegistry::getPassRegistry();
  // initializeC2xxDAGToDAGISelPass(PR);
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  return "e-m:e-p:16:16-i32:16-i64:16-f32:16-f64:16-a:8-n8:16-S16";
}

C2xxTargetMachine::C2xxTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      //TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

C2xxTargetMachine::~C2xxTargetMachine() = default;

// namespace {
// /// C2xx Code Generator Pass Configuration Options.
// class C2xxPassConfig : public TargetPassConfig {
// public:
//   C2xxPassConfig(C2xxTargetMachine &TM, PassManagerBase &PM)
//     : TargetPassConfig(TM, PM) {}

//   C2xxTargetMachine &getC2xxTargetMachine() const {
//     return getTM<C2xxTargetMachine>();
//   }

//   void addIRPasses() override;
//   bool addInstSelector() override;
//   void addPreEmitPass() override;
// };
// } // namespace

// TargetPassConfig *C2xxTargetMachine::createPassConfig(PassManagerBase &PM) {
//   return new C2xxPassConfig(*this, PM);
// }

// MachineFunctionInfo *C2xxTargetMachine::createMachineFunctionInfo(
//     BumpPtrAllocator &Allocator, const Function &F,
//     const TargetSubtargetInfo *STI) const {
//   return C2xxMachineFunctionInfo::create<C2xxMachineFunctionInfo>(Allocator,
//                                                                       F, STI);
// }

// void C2xxPassConfig::addIRPasses() {
//   addPass(createAtomicExpandLegacyPass());
//   TargetPassConfig::addIRPasses();
// }

// bool C2xxPassConfig::addInstSelector() {
//   Install an instruction selector.
//   addPass(createC2xxISelDag(getC2xxTargetMachine(), getOptLevel()));
//   return false;
// }
