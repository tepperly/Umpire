//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#include "umpire/resource/SyclDeviceResourceFactory.hpp"

#include "umpire/resource/SyclDeviceMemoryResource.hpp"
#include "umpire/resource/DefaultMemoryResource.hpp"
#include "umpire/alloc/SyclMallocAllocator.hpp"

#include <CL/sycl.hpp>

#include "umpire/util/Macros.hpp"
#include "umpire/util/make_unique.hpp"

namespace umpire {
namespace resource {

bool
SyclDeviceResourceFactory::isValidMemoryResourceFor(const std::string& name)
  noexcept
{
  if (name.find("DEVICE") != std::string::npos) {
    return true;
  } else {
    return false;
  }
}

std::unique_ptr<resource::MemoryResource>
SyclDeviceResourceFactory::create(const std::string& name, int id)
{
  return create(name, id, getDefaultTraits());
}

std::unique_ptr<resource::MemoryResource>
SyclDeviceResourceFactory::create(const std::string& name, int id, MemoryResourceTraits traits)
{
  return
    util::make_unique<resource::SyclDeviceMemoryResource>(Platform::sycl, name, id, traits);
}

MemoryResourceTraits
SyclDeviceResourceFactory::getDefaultTraits()
{
  MemoryResourceTraits traits;

  cl::sycl::gpu_selector gpuSelect;
  cl::sycl::device sycl_device(gpuSelect);
  const std::string deviceName = sycl_device.get_info<cl::sycl::info::device::name>();
  if (sycl_device.is_gpu() && (deviceName.find("Intel") != std::string::npos)) {
    traits.size = sycl_device.get_info<cl::sycl::info::device::global_mem_size>(); // in bytes
    traits.unified = false;

    traits.id = 0;
    traits.deviceID = sycl_device.get();

    traits.vendor = MemoryResourceTraits::vendor_type::INTEL;
    traits.kind = MemoryResourceTraits::memory_type::GDDR;
    traits.used_for = MemoryResourceTraits::optimized_for::any;
  }

  return traits;
}

} // end of namespace resource
} // end of namespace umpire