//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
//
// Created by David Beckingsale, david@llnl.gov
// LLNL-CODE-747640
//
// All rights reserved.
//
// This file is part of Umpire.
//
// For details, see https://github.com/LLNL/Umpire
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////
#include "umpire/op/HostMemsetOperation.hpp"

#include <cstring>

#include "umpire/util/Macros.hpp"

namespace umpire {
namespace op {

void
HostMemsetOperation::apply(
    void* src_ptr,
    util::AllocationRecord* UMPIRE_UNUSED_ARG(allocation),
    int value,
    std::size_t length)
{
  std::memset(src_ptr, value, length);

  UMPIRE_RECORD_STATISTIC(
      "HostMemsetOperation",
      "src_ptr", reinterpret_cast<uintptr_t>(src_ptr),
      "value", value,
      "size", length,
      "event", "memset");
}

} // end of namespace op
} // end of namespace umpire
