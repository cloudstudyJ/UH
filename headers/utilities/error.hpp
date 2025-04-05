#pragma once

#include "utilities/types.hpp"

// if (expr == true (expr != 0)) -> run action
#define _INTERNAL_RUN_IF(expr, action)  \
    do {                                \
        int _internalResult = (expr);   \
                                        \
        if (_internalResult)            \
            action;                     \
    } while(false)

// max args = 3, support args = { 2, 3 }
#define _INTERNAL_LOG_SELECTOR(_1, _2, _3, FUNC_NAME, ...) FUNC_NAME
#define _INTERNAL_LOG_2(logType, message)                                   \
    UH::Debug::Log::print(logType, message, 0, __FILE__, __LINE__)
#define _INTERNAL_LOG_3(logType, message, errCode)                          \
    UH::Debug::Log::print(logType, message, errCode, __FILE__, __LINE__)

// UH_LOG(logType, message, [optional]: errCode)
#define UH_LOG(...)                                                                     \
    _INTERNAL_LOG_SELECTOR(__VA_ARGS__, _INTERNAL_LOG_3, _INTERNAL_LOG_2)(__VA_ARGS__)
#ifdef DEBUG
#define UH_THROW(throwType, message, errCode)                                           \
    UH::Debug::Throw::except(throwType, message, errCode, __FILE__, __LINE__)
#endif

#ifdef DEBUG
// if (expr == true (expr != 0)) -> throw
#define UH_CHECK_THROW(expr, throwType, message)                            \
    _INTERNAL_RUN_IF(expr, UH_THROW(throwType, message, _internalResult))
#endif
// if (expr == true (expr != 0)) -> log
#define UH_CHECK_LOG(expr, logType, ...)                                    \
    _INTERNAL_RUN_IF(expr, UH_LOG(logType, __VA_ARGS__))

namespace UH {
    namespace Debug {
        class Log {
            Log() = delete;
            Log(const Log&) = delete;
            Log(Log&&) noexcept = delete;
            ~Log() noexcept = delete;

            Log& operator=(const Log&) = delete;
            Log& operator=(Log&&) noexcept = delete;

            public:
                enum class Type: uint8 {
                    INFO    = 1,
                    WARNING = 2,
                    ERROR   = 3
                };

            public:
                static void print(
                    UH::Debug::Log::Type logType, const char* message, int errCode = { },
                    const char* file = "", int line = { }
                ) noexcept;
        };

#ifdef DEBUG
        class Throw {
            Throw() = delete;
            Throw(const Throw&) = delete;
            Throw(Throw&&) noexcept = delete;
            ~Throw() noexcept = delete;

            Throw& operator=(const Throw&) = delete;
            Throw& operator=(Throw&&) noexcept = delete;

            public:
                enum class Type: uint8 {
                    RUNTIME = 1
                };

            public:
                static void except(
                    UH::Debug::Throw::Type throwType, const char* message, int errCode,
                    const char* file, int line
                );
        };
#endif
    }
}

using logType   = UH::Debug::Log::Type;
#ifdef DEBUG
using throwType = UH::Debug::Throw::Type;
#endif