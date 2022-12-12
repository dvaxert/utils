#include "wormhole/utils/log.h"
#include "wormhole/utils/logger/spdlog_logger.h"

namespace wormhole {
namespace utils {

std::shared_ptr<wormhole::utils::ILogger> LoggerSingleton() {
  static auto logger = std::make_shared<wormhole::utils::Logger>();
  return logger;
}

}  // namespace utils
}  // namespace wormhole
