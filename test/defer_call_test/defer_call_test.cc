#if _MSC_VER
#pragma warning(disable : 4319)
#pragma warning(disable : 4244)
#endif

#include <gtest/gtest.h>
#include <wormhole/utils/defer_call.h>

class TestingClass {
 public:
  void SetTrue() { value_ = true; }
  void SetValue(bool v) { value_ = v; }
  bool GetValue() const { return value_; }

 private:
  bool value_{false};
};

//------------------------------------------------------------------------------

TEST(DeferCall, lambda_call) {
  bool ok = false;
  {
    DEFER_CALL([&] { ok = true; });
    ASSERT_FALSE(ok);
  }
  ASSERT_TRUE(ok);
}

//------------------------------------------------------------------------------

TEST(DeferCall, method_call) {
  auto tc = TestingClass();
  {
    DEFER_CALL(&TestingClass::SetTrue, std::ref(tc));
    ASSERT_FALSE(tc.GetValue());
  }
  ASSERT_TRUE(tc.GetValue());
}

//------------------------------------------------------------------------------

TEST(DeferCall, call_order) {
  bool ok1 = false;
  bool ok2 = false;
  bool ok3 = false;

  {
    DEFER_CALL([&] { ok1 = true; });
    ASSERT_FALSE(ok1);
    ASSERT_FALSE(ok2);
    ASSERT_FALSE(ok3);
    {
      DEFER_CALL([&] { ok2 = true; });
      ASSERT_FALSE(ok1);
      ASSERT_FALSE(ok2);
      ASSERT_FALSE(ok3);

      {
        DEFER_CALL([&] { ok3 = true; });
        ASSERT_FALSE(ok1);
        ASSERT_FALSE(ok2);
        ASSERT_FALSE(ok3);
      }
      ASSERT_FALSE(ok1);
      ASSERT_FALSE(ok2);
      ASSERT_TRUE(ok3);
    }
    ASSERT_FALSE(ok1);
    ASSERT_TRUE(ok2);
    ASSERT_TRUE(ok3);
  }
  ASSERT_TRUE(ok1);
  ASSERT_TRUE(ok2);
  ASSERT_TRUE(ok3);
}

//------------------------------------------------------------------------------

TEST(DeferCall, lambda_with_args_call) {
  bool ok = false;
  {
    DEFER_CALL([](bool& val) { val = true; }, std::ref(ok));
    ASSERT_FALSE(ok);
  }
  ASSERT_TRUE(ok);
}

//------------------------------------------------------------------------------

TEST(DeferCall, method_with_args_call) {
  auto tc = TestingClass();
  {
    DEFER_CALL(&TestingClass::SetValue, &tc, true);
    ASSERT_FALSE(tc.GetValue());
  }
  ASSERT_TRUE(tc.GetValue());
}
