///
/// \file MonitoringInternalException.cxx
/// \author Adam Wegrzynek <adam.wegrzynek@cern.ch>
///

#include "MonitoringInternalException.h"
#include "../MonInfoLogger.h"

namespace AliceO2
{
/// ALICE O2 Monitoring system
namespace Monitoring
{

using AliceO2::InfoLogger::InfoLogger;

MonitoringInternalException::MonitoringInternalException(const std::string& source, const std::string& message) :
  MonitoringInternalException(-1, source, message) {}

MonitoringInternalException::MonitoringInternalException(int code, const std::string& source, const std::string& message)
: message(message)
{
  MonInfoLogger::Get() << InfoLogger::Severity::Debug << "MonitoringInternalException["
                       << source << "] (" << code << "): " << message << InfoLogger::endm;
}

const char* MonitoringInternalException::what() const throw()
{
  return message.c_str();
}

} // Monitroing
} // AliceO2