//===- AMDGPURegisterBankInfo -----------------------------------*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file
/// This file declares the targeting of the RegisterBankInfo class for AMDGPU.
/// \todo This should be generated by TableGen.
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_AMDGPU_AMDGPUREGISTERBANKINFO_H
#define LLVM_LIB_TARGET_AMDGPU_AMDGPUREGISTERBANKINFO_H

#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"

namespace llvm {

class SIRegisterInfo;
class TargetRegisterInfo;

namespace AMDGPU {
enum {
  SGPRRegBankID = 0,
  VGPRRegBankID = 1,
  NumRegisterBanks
};
} // End AMDGPU namespace.

/// This class provides the information for the target register banks.
class AMDGPUGenRegisterBankInfo : public RegisterBankInfo {

protected:

#define GET_TARGET_REGBANK_CLASS
#include "AMDGPUGenRegisterBank.inc"

};
class AMDGPURegisterBankInfo : public AMDGPUGenRegisterBankInfo {
  const SIRegisterInfo *TRI;

  /// See RegisterBankInfo::applyMapping.
  void applyMappingImpl(const OperandsMapper &OpdMapper) const override;

  RegisterBankInfo::InstructionMapping
  getInstrMappingForLoad(const MachineInstr &MI) const;

public:
  AMDGPURegisterBankInfo(const TargetRegisterInfo &TRI);

  unsigned copyCost(const RegisterBank &A, const RegisterBank &B,
                    unsigned Size) const override;

  const RegisterBank &
  getRegBankFromRegClass(const TargetRegisterClass &RC) const override;

  InstructionMappings
  getInstrAlternativeMappings(const MachineInstr &MI) const override;

  InstructionMapping getInstrMapping(const MachineInstr &MI) const override;
};
} // End llvm namespace.
#endif
