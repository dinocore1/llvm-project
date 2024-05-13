#include "C2xxMachineFunctionInfo.h"

using namespace llvm;

void C2xxMachineFunctionInfo::anchor() { }

MachineFunctionInfo *C2xxMachineFunctionInfo::clone(
    BumpPtrAllocator &Allocator, MachineFunction &DestMF,
    const DenseMap<MachineBasicBlock *, MachineBasicBlock *> &Src2DstMBB)
    const {
  return DestMF.cloneInfo<C2xxMachineFunctionInfo>(*this);
}
