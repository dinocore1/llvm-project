#include "C2xxMCTargetDesc.h"
#include "C2xxInstPrinter.h"
#include "C2xxMCAsmInfo.h"
#include "TargetInfo/C2xxTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "C2xxGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "C2xxGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "C2xxGenRegisterInfo.inc"

static MCInstrInfo *createC2xxMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitC2xxMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createC2xxMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitC2xxMCRegisterInfo(X, C2xx::PC);
  return X;
}

static MCAsmInfo *createC2xxMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new C2xxMCAsmInfo(TT);

  // Initialize initial frame state.
  int stackGrowth = -2;

  // Initial state of the frame pointer is sp+ptr_size.
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(
      nullptr, MRI.getDwarfRegNum(C2xx::SP, true), -stackGrowth);
  MAI->addInitialFrameState(Inst);

  // Add return address to move list
  MCCFIInstruction Inst2 = MCCFIInstruction::createOffset(
      nullptr, MRI.getDwarfRegNum(C2xx::PC, true), stackGrowth);
  MAI->addInitialFrameState(Inst2);

  return MAI;
}

static MCSubtargetInfo *
createC2xxMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createC2xxMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

static MCInstPrinter *createC2xxMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new C2xxInstPrinter(MAI, MII, MRI);
  return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeC2xxTargetMC() {
  Target &T = getTheC2xxTarget();

  TargetRegistry::RegisterMCAsmInfo(T, createC2xxMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(T, createC2xxMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createC2xxMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createC2xxMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(T, createC2xxMCInstPrinter);
  TargetRegistry::RegisterMCCodeEmitter(T, createC2xxMCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(T, createC2xxMCAsmBackend);
  // TargetRegistry::RegisterObjectTargetStreamer(T, createC2xxObjectTargetStreamer);
}
