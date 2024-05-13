#ifndef LLVM_LIB_TARGET_C2XX_C2XXINSTRINFO_H
#define LLVM_LIB_TARGET_C2XX_C2XXINSTRINFO_H

#include "C2xxRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "C2xxGenInstrInfo.inc"

namespace llvm {

class C2xxSubtarget;

class C2xxInstrInfo : public C2xxGenInstrInfo {
  const C2xxRegisterInfo RI;
  virtual void anchor();
public:
  explicit C2xxInstrInfo(C2xxSubtarget &STI);

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  const C2xxRegisterInfo &getRegisterInfo() const { return RI; }

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc) const override;

  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, Register SrcReg,
                           bool isKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI,
                           Register VReg) const override;
  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, Register DestReg,
                            int FrameIdx, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI,
                            Register VReg) const override;

  unsigned getInstSizeInBytes(const MachineInstr &MI) const override;

  // Branch folding goodness
  bool
  reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const override;
  bool analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TBB,
                     MachineBasicBlock *&FBB,
                     SmallVectorImpl<MachineOperand> &Cond,
                     bool AllowModify) const override;

  unsigned removeBranch(MachineBasicBlock &MBB,
                        int *BytesRemoved = nullptr) const override;
  unsigned insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
                        MachineBasicBlock *FBB, ArrayRef<MachineOperand> Cond,
                        const DebugLoc &DL,
                        int *BytesAdded = nullptr) const override;

  int64_t getFramePoppedByCallee(const MachineInstr &I) const {
    assert(isFrameInstr(I) && "Not a frame instruction");
    assert(I.getOperand(1).getImm() >= 0 && "Size must not be negative");
    return I.getOperand(1).getImm();
  }
};

}

#endif
