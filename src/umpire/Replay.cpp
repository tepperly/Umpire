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

#include <iostream>   // for std::cout, std::cerr
#include <stdlib.h>   // for getenv()

#if !defined(_MSC_VER)
#include <strings.h>  // for strcasecmp()
#include <unistd.h>   // getpid()
#else
#include <process.h>
#define strcasecmp _stricmp
#define getpid _getpid
#endif

#include "umpire/Allocator.hpp"
#include "umpire/strategy/AllocationStrategy.hpp"
#include "umpire/strategy/DynamicPool.hpp"

#include "umpire/util/IOManager.hpp"

#include "umpire/Replay.hpp"

namespace umpire {

static const char* env_name = "UMPIRE_REPLAY";
int Replay::m_argument_number = 0;

Replay::Replay() : m_replayUid(getpid())
{
  char* enval = getenv(env_name);
  bool enable_replay = ( enval != NULL );

  replayEnabled =  enable_replay;
}

void Replay::logMessage( const std::string& message )
{
  if ( !replayEnabled )
    return;   /* short-circuit */

  umpire::replay << message;
}

bool Replay::replayLoggingEnabled()
{
  return replayEnabled;
}

Replay* Replay::getReplayLogger()
{
  static Replay replay;

  return &replay;
}

std::ostream& operator<< (std::ostream& out, umpire::Allocator& alloc) {
  out << alloc.getName();
  return out;
}

std::ostream& operator<< (
    std::ostream& out, 
    umpire::strategy::DynamicPool::Coalesce_Heuristic& ) {
  return out;
}

} /* namespace umpire */
