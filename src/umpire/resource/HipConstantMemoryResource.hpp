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
#ifndef UMPIRE_HipConstantMemoryResource_HPP
#define UMPIRE_HipConstantMemoryResource_HPP

#include "umpire/resource/MemoryResource.hpp"

#include "umpire/util/AllocationRecord.hpp"
#include "umpire/util/Platform.hpp"

#include <hip/hip_runtime.h>

__constant__ char umpire_internal_device_constant_memory[64*1024];

namespace umpire {
namespace resource {


class HipConstantMemoryResource :
  public MemoryResource
{
  public:
    HipConstantMemoryResource(const std::string& name, int id, MemoryResourceTraits traits);

    void* allocate(std::size_t bytes);
    void deallocate(void* ptr);

    long getCurrentSize() const noexcept;
    long getHighWatermark() const noexcept;

    Platform getPlatform() noexcept;

  private:
    long m_current_size;
    long m_highwatermark;

    Platform m_platform;

    std::size_t m_offset;
    void* m_ptr;
};

} // end of namespace resource
} // end of namespace umpire

#endif // UMPIRE_HipConstantMemoryResource_HPP
