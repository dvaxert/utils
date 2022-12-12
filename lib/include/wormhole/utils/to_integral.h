#ifndef UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_
#define UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_

#include <type_traits>

namespace wormhole {
namespace utils {

template <typename TEnum>
constexpr auto to_integral(TEnum value) {
  return static_cast<typename std::underlying_type_t<TEnum>>(value);
}

}  // namespace utils
}  // namespace wormhole

#endif  // UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_
