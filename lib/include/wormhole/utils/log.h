﻿#ifndef UTILS_LIB_INCLUDE_WORMHOLE_UTILS_LOG_H_
#define UTILS_LIB_INCLUDE_WORMHOLE_UTILS_LOG_H_

#include <fmt/format.h>

#include <boost/preprocessor.hpp>
#include <memory>
#include <sstream>

#include "wormhole/utils/defer_call.h"
#include "wormhole/utils/logger/ilogger.h"
#include "wormhole/utils/logger/level.h"

#ifndef UTILS_DISABLE_LOG

/**
 * @brief Set the logging level
 * @param level { Trace, Debug, Info, Warning, Error, Fatal }
 */
#define SET_LOG_LEVEL(level) wormhole::utils::LoggerSingleton()->SetLevel(wormhole::utils::LogLevel::level);

/**
 * @brief Sending a message
 * @param msg message
 */
#define LOG_TRACE(msg) wormhole::utils::LoggerSingleton()->Trace(msg);
#define LOG_DEBUG(msg) wormhole::utils::LoggerSingleton()->Debug(msg);
#define LOG_INFO(msg) wormhole::utils::LoggerSingleton()->Info(msg);
#define LOG_WARNING(msg) wormhole::utils::LoggerSingleton()->Warning(msg);
#define LOG_ERROR(msg) wormhole::utils::LoggerSingleton()->Error(msg);
#define LOG_FATAL(msg) wormhole::utils::LoggerSingleton()->Fatal(msg);

/**
 * @brief Notification of entering and exiting the function
 */
#define TRACE_LOG()                                                                          \
  wormhole::utils::LoggerSingleton()->Trace(fmt::format("enter {}()", GET_FUNCTION_NAME())); \
  DEFER_CALL(&wormhole::utils::ILogger::Trace, wormhole::utils::LoggerSingleton(),           \
             fmt::format("exit {}()", GET_FUNCTION_NAME()));

/**
 * @brief Message about entering and exiting a function with information about
 *        the arguments passed at the call
 */
#define TRACE_LOG_P(...) \
  TRACE_LOG()            \
  LOG_PARAMS(__VA_ARGS__)

#define GET_FUNCTION_NAME() __func__

/**
 * @brief Message displaying the arguments of the function call
 *
 * @warning The passed parameters must have the << operator to work with std
 *          streams
 */
#define PRINT_PARAM(r, data, elem) data << fmt::format("\t{} = {}\n", #elem, elem);
#define LOG_PARAMS(...)                                                              \
  {                                                                                  \
    std::ostringstream tmp{};                                                        \
    tmp << GET_FUNCTION_NAME() << " call arguments:\n";                              \
    BOOST_PP_LIST_FOR_EACH(PRINT_PARAM, tmp, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__)) \
    std::string res = tmp.str();                                                     \
    res.pop_back();                                                                  \
    LOG_TRACE(res);                                                                  \
  }

namespace wormhole {
namespace utils {
/**
 * @brief Singleton for a single logger for the entire application
 */
std::shared_ptr<wormhole::utils::ILogger> LoggerSingleton();

}  // namespace utils
}  // namespace wormhole

#else  // UTILS_DISABLE_LOG

#define SET_LOG_LEVEL(...) void();
#define LOG_TRACE(...) void();
#define LOG_DEBUG(...) void();
#define LOG_INFO(...) void();
#define LOG_WARNING(...) void();
#define LOG_ERROR(...) void();
#define LOG_FATAL(...) void();
#define TRACE_LOG(...) void();
#define TRACE_LOG_P(...) void();
#define PRINT_PARAM(...) void();
#define LOG_PARAMS(...) void();
#define GET_FUNCTION_NAME() void();

#endif  // UTILS_DISABLE_LOG

#endif  // UTILS_LIB_INCLUDE_WORMHOLE_UTILS_LOG_H_
