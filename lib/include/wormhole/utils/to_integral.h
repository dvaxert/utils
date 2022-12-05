#ifndef UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_
#define UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_

#include <type_traits>

namespace wh {
namespace utils {

template <typename TEnum>
constexpr auto to_integral(TEnum value) {
  return static_cast<typename std::underlying_type_t<TEnum>>(value);
}

}  // namespace utils
}  // namespace wh

#endif  // UTILS_LIB_INCLUDE_UTILS_TO_INTEGRAL_H_
