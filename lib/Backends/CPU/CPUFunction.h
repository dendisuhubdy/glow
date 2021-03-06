/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GLOW_BACKENDS_CPU_CPUFUNCTION_H
#define GLOW_BACKENDS_CPU_CPUFUNCTION_H

#include "GlowJIT.h"

#include "glow/Backends/CompiledFunction.h"

namespace glow {

/// A Glow IR function compiled for the CPU using LLVM.
class CPUFunction final : public CompiledFunction {
  /// The LLVM JIT engine. The jit must be initialized after the ctor
  /// initializes the LLVM backends.
  std::unique_ptr<llvm::orc::GlowJIT> JIT_;
  /// runtimeBundle contains symbol offsets and allocation sizes.
  runtime::RuntimeBundle runtimeBundle_;
  /// Base address for Activations memory block.
  uint8_t *baseActivationsAddress_;
  /// Base address for Mutable weights memory block, Inputs and Outputs.
  uint8_t *baseMutableWeightVarsAddress_;

public:
  /// Ctor.
  CPUFunction(std::unique_ptr<llvm::orc::GlowJIT> JIT,
              const runtime::RuntimeBundle &runtimeBundle);
  /// Copy Function to device, an empty function for CPU.
  void copyFunctionToDevice(){};
  /// Copy Constants to device, an empty function for CPU.
  void copyConstantsToDevice(){};
  /// Allocate Mutable buffers on device this includes Activations and
  /// Placeholders.
  void allocateMutableBuffersOnDevice();
  /// Copy Input Placeholder data to device.
  void copyInputsToDevice(Context &ctx);
  /// Copy Outputs from Device to Placeholders in \p ctx.
  void copyOutputsFromDevice(Context &ctx);
  /// Free all allocations.
  void freeAllocations();
  /// \name CompiledFunction interface
  ///@{
  ~CPUFunction() override;
  void execute(Context &ctx) override;
  ///@}
};
} // end namespace glow

#endif // GLOW_BACKENDS_CPU_CPUFUNCTION_H
