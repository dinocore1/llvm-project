#ifndef LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXMCTARGETDESC_H
#define LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class Target;
class MCAsmBackend;
class MCCodeEmitter;
class MCInstrInfo;
class MCSubtargetInfo;
class MCRegisterInfo;
class MCContext;
class MCTargetOptions;
class MCObjectTargetWriter;
class MCStreamer;
class MCTargetStreamer;

/// Creates a machine code emitter for C2xx.
MCCodeEmitter *createC2xxMCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx);

MCAsmBackend *createC2xxMCAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const MCTargetOptions &Options);

MCTargetStreamer *
createC2xxObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

std::unique_ptr<MCObjectTargetWriter>
createC2xxELFObjectWriter(uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for C2xx registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "C2xxGenRegisterInfo.inc"

// Defines symbolic names for the C2xx instructions.
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "C2xxGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "C2xxGenSubtargetInfo.inc"

#endif
