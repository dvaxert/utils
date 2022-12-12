#include <gtest/gtest.h>
#include <wormhole/utils/condition_variable.h>

#include <thread>

using namespace std::chrono_literals;

//------------------------------------------------------------------------------

TEST(ConditionVariableTest, get_status) {
  auto cv = wormholeutils::ConditionVariable();
  ASSERT_FALSE(cv.Get());

  cv.Notify();
  ASSERT_TRUE(cv.Get());

  cv.Reset();
  ASSERT_FALSE(cv.Get());

  cv.Notify();
  ASSERT_TRUE(cv.Get());
}

//------------------------------------------------------------------------------

TEST(ConditionVariableTest, waiting_timeout) {
  auto cv = wormholeutils::ConditionVariable();
  auto start = std::chrono::system_clock::now();
  cv.WaitFor(1000ms);
  auto end = std::chrono::system_clock::now();

  ASSERT_GE(end - start, 1000ms);
}

//------------------------------------------------------------------------------

TEST(ConditionVariableTest, waiting_deadline) {
  auto cv = wormholeutils::ConditionVariable();
  auto start = std::chrono::system_clock::now();
  cv.WaitUntil(start + 1000ms);
  auto end = std::chrono::system_clock::now();

  ASSERT_GE(end - start, 1000ms);
}

//------------------------------------------------------------------------------

TEST(ConditionVariableTest, notify_with_timeout) {
  auto cv = wormholeutils::ConditionVariable();
  auto start = std::chrono::system_clock::now();
  auto t = std::thread([&] {
    std::this_thread::sleep_for(300ms);
    cv.Notify();
  });

  cv.WaitFor(1000ms);
  auto end = std::chrono::system_clock::now();

  ASSERT_LT(end - start, 1000ms);
  ASSERT_GE(end - start, 300ms);
  t.join();
}

//------------------------------------------------------------------------------

TEST(ConditionVariableTest, notify_with_deadline) {
  auto cv = wormholeutils::ConditionVariable();
  auto start = std::chrono::system_clock::now();
  auto t = std::thread([&] {
    std::this_thread::sleep_for(300ms);
    cv.Notify();
  });

  cv.WaitUntil(start + 1000ms);
  auto end = std::chrono::system_clock::now();

  ASSERT_LT(end - start, 1000ms);
  ASSERT_GE(end - start, 300ms);
  t.join();
}
