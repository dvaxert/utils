#ifndef UTILS_LIB_INCLUDE_UTILS_CONDITION_VARIABLE_H_
#define UTILS_LIB_INCLUDE_UTILS_CONDITION_VARIABLE_H_

#include <cstdint>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace wh {
namespace utils {

class ConditionVariable {
  public:
    ConditionVariable() = default;
    ~ConditionVariable() = default;

    bool Get() const;
    bool WaitFor(uint64_t timeout_ms);
    void Notify();
    void Reset();

    operator bool() const;

  private:
    std::condition_variable cv_;
    std::atomic_bool bool_;
    std::mutex mutex_;
};
    
}
}

#endif // UTILS_LIB_INCLUDE_UTILS_CONDITION_VARIABLE_H_
