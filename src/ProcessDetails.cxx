///
/// \file Tags.cxx
/// \author Adam Wegrzynek <adam.wegrzynek@cern.ch>
///

#include "ProcessDetails.h"

#include <unistd.h>

#ifdef _OS_MAC
#include <mach-o/dyld.h>
#endif

namespace AliceO2
{
/// ALICE O2 Monitoring system
namespace Monitoring
{

ProcessDetails::ProcessDetails()
{
  generatePid();
  generateProcessName();
  generateHostname();
}

inline void ProcessDetails::generatePid()
{
  mPid = ::getpid();
}

inline void ProcessDetails::generateProcessName()
{
  char buff[255];
  #ifdef _OS_LINUX
  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
    mProcessName = std::string(buff);
  }
  #endif

  #ifdef _OS_MAC
  uint32_t size = sizeof(buff);
  if (_NSGetExecutablePath(buff, &size) == 0) {
    mProcessName = std::string(buff);
  }
  #endif

  if (mProcessName.empty()) {
    mProcessName = "!";
  } else {
    mProcessName = mProcessName.substr(mProcessName.find_last_of("/") + 1);
  }
}

inline void ProcessDetails::generateHostname()
{
  char hostname[255];
  gethostname(hostname, 255);
  mHostname = std::string(hostname);
}

unsigned int ProcessDetails::getPid() const
{
  return mPid;
}

std::string ProcessDetails::getProcessName() const
{
  return mProcessName;
}

std::string ProcessDetails::getHostname() const
{
  return mHostname;
}

} // namespace Monitoring
} // namespace AliceO2
