#include "utilities/error.hpp"

#include <iostream>
#include <format>

/**
 * Return
 *   enum class UH::Debug::Type의 값을 const char*로 변환하여 반환
 */
const char* toString(UH::Debug::Log::Type logType) {
    switch (logType) {
        case UH::Debug::Log::Type::INFO   : return "INFO";
        case UH::Debug::Log::Type::WARNING: return "WARNING";
        case UH::Debug::Log::Type::ERROR  : return "ERROR";

        default: return "UNKNOWN";
    }
}
/**
 * Return
 *   debugType이 UH::Debug::Type::ERROR 이면, "[file:line]" string 반환
 *   debugType이 UH::Debug::Type::ERROR 이 아니면, empty string ("") 반환
 */
std::string extraInfo(UH::Debug::Log::Type logType, const char* file, int line) {
    if (logType == UH::Debug::Log::Type::ERROR)
        return std::format("  [{}:{}]", file, line);

    return "";
}
/**
 * Return
 *   errCode가 0 이면, "(CODE: {})" string 반환
 *   errCode가 0 이 아니면, empty string ("") 반환
 */
std::string codeInfo(int errCode) {
    if (errCode != 0)
        return std::format("(CODE: {})", errCode);

    return "";
}

// log print function with errCode
void UH::Debug::Log::print(UH::Debug::Log::Type logType, const char* message, int errCode, const char* file, int line) noexcept {
    std::string notice = std::format(
        "[{}] {} {}\n"
        "{}",
        toString(logType), message,
        codeInfo(errCode), extraInfo(logType, file, line)
    );

    std::cout << notice << std::endl;
}

#ifdef DEBUG
void UH::Debug::Throw::except(UH::Debug::Throw::Type throwType, const char* message, int errCode, const char* file, int line) {
    UH::Debug::Log::print(UH::Debug::Log::Type::ERROR, message, errCode, file, line);

    throw std::runtime_error("");
}
#endif