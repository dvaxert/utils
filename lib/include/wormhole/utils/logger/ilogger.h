#ifndef UTILS_LIB_INCLUDE_UTILS_LOGGER_ILOGGER_H_
#define UTILS_LIB_INCLUDE_UTILS_LOGGER_ILOGGER_H_

#include <string_view>

#include "wormhole/utils/logger/level.h"

namespace wh {
namespace utils {

class ILogger {
 public:
  virtual ~ILogger() = default;

  virtual void Trace(const std::string_view message) = 0;
  virtual void Debug(const std::string_view message) = 0;
  virtual void Info(const std::string_view message) = 0;
  virtual void Warning(const std::string_view message) = 0;
  virtual void Error(const std::string_view message) = 0;
  virtual void Fatal(const std::string_view message) = 0;

  virtual void SetLevel(const wh::utils::LogLevel level) = 0;
};

}  // namespace utils
}  // namespace wh

#endif  // UTILS_LIB_INCLUDE_UTILS_LOGGER_ILOGGER_H_
