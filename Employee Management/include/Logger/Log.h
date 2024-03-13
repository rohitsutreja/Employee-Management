#ifndef LOG_H
#define LOG_H

#include "../Util.h"
#include "../Util.h"
#include <chrono>


namespace MyLogger
{
    class Log
    {
    public:
        enum class Level
        {
            Debug = 0,
            Info,
            Warning,
            Error,
            Critical
        };

    private:
        Level m_LogLevel;
        bool m_dumpInFile{ true };
        std::string m_fPath{ ".\\logs\\logs.txt" };
        mutable std::string m_buffer{ };
        mutable int m_bufferCount{};

        std::string getLevelName(Level l) const;
        std::string getColoredLevelName(Level l) const;


    public:
        Log() : m_LogLevel{ Level::Info } {}
        explicit Log(Level level, std::string filePath) : m_LogLevel{ level }, m_fPath{ filePath } {}

        void setLevel(Level level) { m_LogLevel = level; }
        void setFilePath(std::string path) { m_fPath = path; }
        void setDumpInFileFlag(bool f) { m_dumpInFile = f; }

        constexpr Level getLevel() const { return m_LogLevel; }


        void logOnConsole(const std::string& msg) const;
        void logOnFile(const std::string& msg, const std::string& fileName) const;
        void flushOnFile() const;

        ~Log();


        template <typename... Types>
        void log(Level level, const Types&... message) const
        {
            if (level >= m_LogLevel)
            {
                std::string dateTimeString = getLogTimeString();
                std::string messageString =  getString(message...);
                std::string finalMessageForConsole = dateTimeString + " [" + getColoredLevelName(level) + "] " + messageString + "\n";


              //  logOnConsole(finalMessageForConsole);

                if (m_dumpInFile == true)
                {
                    std::string finalMessageForFile = dateTimeString + " [" + getLevelName(level) + "] " + messageString + "\n";
                    m_buffer.append(finalMessageForFile);
                    ++m_bufferCount;
                    if (m_bufferCount >= 10) {

                        flushOnFile();

                    }
                }

            }
        }
    };



}

#endif