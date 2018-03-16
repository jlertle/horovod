// Copyright 2018 Uber Technologies, Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#ifndef HOROVOD_TORCH_READY_EVENT_H
#define HOROVOD_TORCH_READY_EVENT_H

#if HAVE_CUDA
#include <mutex>
#include <queue>
#include <unordered_map>
#include "cuda_runtime.h"

#include "../common/common.h"

namespace horovod {
namespace torch {

using namespace horovod::common;

template <class T> class TorchReadyEvent : public ReadyEvent {
public:
  TorchReadyEvent(int device);
  ~TorchReadyEvent();
  virtual bool Ready() const override;

private:
  int device_;
  cudaEvent_t cuda_event_;
  static std::unordered_map<int, std::queue<cudaEvent_t>> cuda_events_;
  static std::mutex mutex_;
};

} // namespace torch
} // namespace horovod
#endif

#endif // HOROVOD_TORCH_READY_EVENT_H