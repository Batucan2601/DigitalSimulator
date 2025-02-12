#include "Logger.h"
namespace utils
{
std::string Logger::logLevelToString(LogLevel level) const
{
    switch (level)
    {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    };
}

void Logger::setLogLevel(LogLevel level)
{
    switch (level)
    {
        case LogLevel::INFO:
        {
            m_logLevel = LogLevel::INFO;
            break;
        }
        case LogLevel::WARNING:
        {
            m_logLevel = LogLevel::WARNING;
            break;
        }
        case LogLevel::ERROR:
        {
            m_logLevel = LogLevel::ERROR;
            break;
        }
        case LogLevel::DEBUG:
        {
            m_logLevel = LogLevel::DEBUG;
            break;
        }
        default:
        {
            printf("Wrong type of input.");
            exit(0);
        }
    }
}

}  // namespace utils