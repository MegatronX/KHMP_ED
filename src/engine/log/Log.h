#pragma once
#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <fstream>
#include <sstream>
class Logger
{
public:
	enum LogLevel
	{
		Debug,
		Warning,
		Error,
		CriticalError
	};
	Logger(LogLevel l, std::ostream* logDest);

	void operator()(const std::string& msg, char const* func, char const* file, int line);
	static void setDebugLog(const std::string& debugFile = "Debug.log");
	static void setErrorLog(const std::string& errorLog = "Error.log");

	const static std::string& getDebugLog();
	const static std::string& getErrorLog();

	static std::ofstream& getDebugLogStream();
	static std::ofstream& getErrorLogStream();
protected:
private:
	static std::string m_debugLog;
	static std::string m_errorLog;
	static std::ofstream m_debugLogStream;
	static std::ofstream m_errorLogStream;
	std::ostream* m_outputStream;
	LogLevel m_level;
};

#if defined NDEBUG || !defined DEBUG 
#  define LOG_DEBUG(_) do {} while(0);
#else
#  define LOG_DEBUG(Message_) LOG(Debug(), Message_)
#endif

#if defined LOG_ERRORS
#define LOG_ERROR(Message_) LOG(Error(), Message_)
#else
#define LOG_ERROR(_) do {} while(0);
#endif

#define LOG(Logger_, Message_)                  \
  Logger_(                                      \
    static_cast<std::ostringstream&>(           \
      std::ostringstream().flush() << Message_  \
    ).str(),                                    \
    __FUNCTION__,                               \
    __FILE__,                                   \
    __LINE__                                    \
  );

extern Logger& Debug();
extern Logger& Error();
#endif