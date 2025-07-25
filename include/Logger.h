#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include "Signal.h"
#ifdef _WIN32
#include <array>
#endif
namespace utils
{
    class Logger
    {
      public:
        enum class LogLevel
        {
            DEBUG,
            ERROR,
            WARNING,
            INFO
        };

        static Logger& getInstance()
        {
            static Logger instance;
            return instance;
        }

        void setLogLevel(LogLevel level);
        Logger::LogLevel parseLogLevel(int argc, char* argv[])
        {
            if (argc > 1)
            {
                std::string arg = argv[1];
                if (arg == "-i")
                {
                    return Logger::LogLevel::INFO;
                }
                else if (arg == "-w")
                {
                    return Logger::LogLevel::WARNING;
                }
                else if (arg == "-e")
                {
                    return Logger::LogLevel::ERROR;
                }
                else if (arg == "-d")
                {
                    return Logger::LogLevel::DEBUG;
                }
                else
                {
                    std::cerr << "Unknown log level argument: " << arg << std::endl;
                    std::cerr << "Usage: " << argv[0] << " [-i | -w | -e]" << std::endl;
                    std::exit(EXIT_FAILURE);
                }
            }

            return Logger::LogLevel::INFO;  // Default log level
        }

        template<typename... Args>
        void log(const std::string& className, LogLevel level, const std::string& format,
                 Args... args)
        {
            if (level < m_logLevel)
                return;

            std::lock_guard<std::mutex> lock(mtx);

            std::string message = formatString(format, args...);

            std::string color_code;
            switch (level)
            {
                case LogLevel::INFO:
                    color_code = "\033[92m";  // Bright Green
                    break;
                case LogLevel::WARNING:
                    color_code = "\033[93m";  // Bright Yellow
                    break;
                case LogLevel::ERROR:
                    color_code = "\033[91m";  // Bright Red
                    break;
                case LogLevel::DEBUG:
                    color_code = "\033[94m";  // Bright Blue
                    break;
                default:
                    color_code = "\033[00m";  // Reset (default terminal color)
                    break;
            }

            std::string color_code_reset = "\033[00m";
            std::string bold = "\u001b[1m";
            std::string black_color = "\033[31m";
            std::string white_color = "\033[37m";

            // Get the current time (cross-platform & thread-safe)
            std::time_t now = std::time(nullptr);
            std::tm timeInfo;

#ifdef _WIN32
            localtime_s(&timeInfo, &now);  // Windows
#else
            localtime_r(&now, &timeInfo);  // Linux/macOS
#endif

            // Format time manually to preserve your formatting
            std::string time = std::to_string(timeInfo.tm_hour) + ":" +
                               std::to_string(timeInfo.tm_min) + ":" +
                               std::to_string(timeInfo.tm_sec);

            std::cout << bold << black_color << "[" << className << "]\t[" << time << "]"
                      << color_code_reset << color_code << " [" << logLevelToString(level) << "]"
                      << color_code_reset << "\t-\t" << bold << white_color << message
                      << color_code_reset << std::endl;
        }

      private:
        LogLevel m_logLevel = LogLevel::INFO;
        std::mutex mtx;

        Logger() = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        template<typename... Args>
        std::string formatString(const std::string& format, Args... args)
        {
            std::ostringstream oss;
            const char* ptr = format.c_str();
            std::array<std::string, sizeof...(Args)> argArray = {toString(args)...};
            size_t argIndex = 0;

            while (*ptr)
            {
                if (*ptr == '{' && *(ptr + 1) == '}' && argIndex < argArray.size())
                {
                    oss << argArray[argIndex++];
                    ptr += 2;  // Skip "{}"
                }
                else
                {
                    oss << *ptr++;
                }
            }

            return oss.str();
        }
        inline std::string toString(Signal s )
        {
            std::ostringstream oss;
            oss << "Signal(name: " << s.name << ", pos: (" << s.pos.x << ", " << s.pos.y
                << "), val: [";
            for (size_t i = 0; i < s.val.size(); ++i)
            {
                oss << toString(s.val[i]);
                if (i < s.val.size() - 1)
                    oss << ", ";
            }
            oss << "], type: " << static_cast<int>(s.type) << ")";
            return oss.str();
        }
        inline std::string toString(std::vector<SignalVal> s )
        {
            std::ostringstream oss;
            for (size_t i = 0; i < s.size(); ++i)
            {
                oss << toString(s[i]);
                if (i < s.size() - 1)
                    oss << ", ";
            }
            return oss.str();
        }
        inline std::string toString(SignalVal val )
        {
            switch (val)
            {
            case  SignalVal::SIGNAL_0: return "SIGNAL_0";
            case  SignalVal::SIGNAL_1: return "SIGNAL_1";
            case  SignalVal::SIGNAL_X: return "SIGNAL_X";
            default:
                return "UNKNOWN SIGNAL";
            }
        }
        template<typename T>
        std::string toString(const T& value)
        {
            if constexpr (std::is_arithmetic<T>::value)
            {
                return std::to_string(value);
            }
            else
            {
                std::ostringstream oss;
                oss << value;
                return oss.str();
            }
        }

        std::string logLevelToString(LogLevel level) const;
    };
}  // namespace utils
#endif  // LOGGER_H