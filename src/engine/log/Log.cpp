#include "Log.h"
#include <stdio.h>
#include <time.h>

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

	return buf;
}


Logger::Logger(LogLevel l, std::ostream* logDest) : m_outputStream(logDest), m_level(l)
{

}
void Logger::setDebugLog(const std::string& debugFile)
{
	if (m_debugLogStream.is_open())
		m_debugLogStream.close();
	m_debugLogStream.open(debugFile.c_str());
	m_debugLog = debugFile;
}
void Logger::setErrorLog(const std::string& errorLog )
{
	if (m_errorLogStream.is_open())
		m_errorLogStream.close();
	m_errorLogStream.open(errorLog.c_str());
	m_errorLog = errorLog;
}

void Logger::operator()(const std::string& msg, char const* func, char const* file, int line)
{
	if (m_outputStream)
	{
		(*m_outputStream) << "[" << currentDateTime().c_str() << "]";
		switch (m_level)
		{
		case Debug:
			(*m_outputStream) << " DEBUG MSG: ";
			break;
		case Error:
			(*m_outputStream) << " ERROR MSG: ";
			break;
		default:
			break;
		}
		(*m_outputStream) << msg.c_str() << " in file " << file << " func " << func << " line " << line << "\n";
		(*m_outputStream).flush();
	}
}

const std::string& Logger::getDebugLog() 
{
	return m_debugLog;
}
const std::string& Logger::getErrorLog() 
{
	return m_errorLog;
}

std::ofstream& Logger::getDebugLogStream()
{
	return m_debugLogStream;
}
std::ofstream& Logger::getErrorLogStream()
{
	return m_errorLogStream;
}

std::string Logger::m_debugLog;
std::string Logger::m_errorLog;
std::ofstream Logger::m_debugLogStream;
std::ofstream Logger::m_errorLogStream;

Logger& Debug()
{
	static Logger debugLogger(Logger::Debug, &Logger::getDebugLogStream());
	return debugLogger;
}

Logger& Error()
{
	static Logger errorLogger(Logger::Error, &Logger::getErrorLogStream());
	return errorLogger;
}