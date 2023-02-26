#include <functional>

#include "wormhole/utils/condition_variable.h"

namespace wormhole {
namespace utils {

bool ConditionVariable::Get() const { return bool_.load(); }

//------------------------------------------------------------------------------

ConditionVariable::operator bool() const { return Get(); }

//------------------------------------------------------------------------------

void ConditionVariable::Notify() {
  bool_.store(true);
  cv_.notify_one();
}

//------------------------------------------------------------------------------

void ConditionVariable::Reset() { bool_.store(false); }

//------------------------------------------------------------------------------

bool ConditionVariable::Wait() {
  auto lock = std::unique_lock(mutex_);
  cv_.wait(lock, std::bind(&ConditionVariable::Get, this));
  return Get();
}

//------------------------------------------------------------------------------

bool ConditionVariable::WaitFor(const std::chrono::milliseconds& timeout) {
  auto lock = std::unique_lock(mutex_);
  cv_.wait_for(lock, timeout, std::bind(&ConditionVariable::Get, this));
  return Get();
}

//------------------------------------------------------------------------------

bool ConditionVariable::WaitUntil(const std::chrono::system_clock::time_point& deadline) {
  auto lock = std::unique_lock(mutex_);
  cv_.wait_until(lock, deadline, std::bind(&ConditionVariable::Get, this));
  return Get();
}

}  // namespace utils
}  // namespace wormhole
