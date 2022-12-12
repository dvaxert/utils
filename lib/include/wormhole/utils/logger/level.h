#ifndef UTILS_LIB_INCLUDE_UTILS_LOGGER_LOG_LEVEL_H_
#define UTILS_LIB_INCLUDE_UTILS_LOGGER_LOG_LEVEL_H_

#include <cstdint>

namespace wormhole {
namespace utils {

enum class LogLevel : uint8_t { Trace, Debug, Info, Warning, Error, Fatal };

}  // namespace utils
}  // namespace wormhole

#endif  // UTILS_LIB_INCLUDE_UTILS_LOGGER_LOG_LEVEL_H_
