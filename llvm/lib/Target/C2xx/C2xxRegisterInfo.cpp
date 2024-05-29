#include "C2xxRegisterInfo.h"
#include "C2xx.h"
#include "C2xxMachineFunctionInfo.h"
#include "C2xxTargetMachine.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "c2xx-reg-info"

#define GET_REGINFO_TARGET_DESC
#define GET_REGINFO_ENUM
#include "C2xxGenRegisterInfo.inc"

// FIXME: Provide proper call frame setup / destroy opcodes.
C2xxRegisterInfo::C2xxRegisterInfo()
  : C2xxGenRegisterInfo(C2xx::PC) {}

const MCPhysReg*
C2xxRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  const C2xxFrameLowering *TFI = getFrameLowering(*MF);
  const Function* F = &MF->getFunction();
  // TODO: handle floating point 
  static const MCPhysReg CalleeSavedRegs[] = {
    C2xx::XAR1, C2xx::XAR2, C2xx::XAR3,
    0
  };
//   static const MCPhysReg CalleeSavedRegsFP[] = {
//     C2xx::R4H, C2xx::R5H C2xx::R6H,
//     C2xx::R7H,
//     0
//   };
  static const MCPhysReg CalleeSavedRegsIntr[] = {
    C2xx::AR1H,  C2xx::AR0H,  C2xx::XT,  C2xx::XAR4,
    C2xx::XAR5,  C2xx::XAR6,  C2xx::XAR7,
    0
  };
//   static const MCPhysReg CalleeSavedRegsIntrFP[] = {
//     C2xx::R5,  C2xx::R6,  C2xx::R7,
//     C2xx::R8,  C2xx::R9,  C2xx::R10, C2xx::R11,
//     C2xx::R12, C2xx::R13, C2xx::R14, C2xx::R15,
//     0
//   };

//   if (TFI->hasFP(*MF))
//     return (F->getCallingConv() == CallingConv::C2XX_INTR ?
//             CalleeSavedRegsIntrFP : CalleeSavedRegsFP);
//   else
//     return (F->getCallingConv() == CallingConv::C2XX_INTR ?
//             CalleeSavedRegsIntr : CalleeSavedRegs);

return (F->getCallingConv() == CallingConv::C2XX_INTR ? 
    CalleeSavedRegsIntr : CalleeSavedRegs);

}

BitVector C2xxRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  const C2xxFrameLowering *TFI = getFrameLowering(MF);

  Reserved.set(C2xx::SP);
  Reserved.set(C2xx::ST0);
  Reserved.set(C2xx::ST1);

  // TODO: are ther other reserved registers?
  

  return Reserved;
}

const TargetRegisterClass *
C2xxRegisterInfo::getPointerRegClass(const MachineFunction &MF, unsigned Kind)
                                                                         const {
  return &C2xx::GP16RegClass;
}

bool
C2xxRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const {
  
  // TODO
  return false;
}

Register C2xxRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const C2xxFrameLowering *TFI = getFrameLowering(MF);

  // TODO: handle floating point
  // return TFI->hasFP(MF) ? C2xx::R4 : C2xx::SP;

  return C2xx::SP;
}
