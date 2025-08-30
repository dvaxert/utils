#ifndef UTILS_LIB_INCLUDE_WORMHOLE_UTILS_INTERFACE_ICONFIG_H_
#define UTILS_LIB_INCLUDE_WORMHOLE_UTILS_INTERFACE_ICONFIG_H_

#include <any>
#include <string>

namespace wormhole {
namespace utils {

class IConfig {
 public:
  virtual ~IConfig() = default;

  virtual bool HasKey(const std::string& key);
  virtual bool HasPath(const std::string& key);
};

}  // namespace utils
}  // namespace wormhole

#endif  // UTILS_LIB_INCLUDE_WORMHOLE_UTILS_INTERFACE_ICONFIG_H_
