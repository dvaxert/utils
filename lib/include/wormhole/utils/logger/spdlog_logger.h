#ifndef UTILS_LIB_INCLUDE_UTILS_LOGGER_LOGGER_H_
#define UTILS_LIB_INCLUDE_UTILS_LOGGER_LOGGER_H_

#include <fmt/format.h>

#include <string_view>

#include "wormhole/utils/fast_pimpl.h"
#include "wormhole/utils/logger/ilogger.h"
#include "wormhole/utils/logger/level.h"

namespace wormhole {
namespace utils {

class Logger : public ILogger {
 public:
  Logger();
  ~Logger() override;

  void Trace(const std::string_view message) override;
  void Debug(const std::string_view message) override;
  void Info(const std::string_view message) override;
  void Warning(const std::string_view message) override;
  void Error(const std::string_view message) override;
  void Fatal(const std::string_view message) override;

  void SetLevel(const LogLevel level) override;

 private:
  class Pimpl;
  utils::FastPimpl<Pimpl, 16, 8> pimpl_;
};

}  // namespace utils
}  // namespace wormhole

#endif  // UTILS_LIB_INCLUDE_UTILS_LOGGER_LOGGER_H_
