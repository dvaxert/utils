#include "wormhole/utils/log.h"
#include "wormhole/utils/logger/spdlog_logger.h"

namespace wh {
namespace utils {

std::shared_ptr<wh::utils::ILogger> LoggerSingleton() {
  static auto logger = std::make_shared<wh::utils::Logger>();
  return logger;
}

}  // namespace utils
}  // namespace wh
