#include "Logger.h"

#include <time.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

void Logger::write()
{
	if (logQueue.size() == 0)
		return;
	
	std::string message = logQueue.pop();
	std::ofstream logFile;

	fileMutex.lock();
	logFile.open(filePath, std::ofstream::out);
	logFile << message;
	logFile.close();
	fileMutex.unlock();
}

Logger::Logger(const std::string logFile)
{
	filePath = logFile;
}

void Logger::addMessage(Log::LogChannel channel, std::string tag, std::string message)
{
	std::string logMessage;
	switch (channel)
	{
	case Log::ERROR:
		logMessage+="[E] ";
		break;
	case Log::DEBUG:
		logMessage+="[D] ";
		break;
	case Log::INFO:
		logMessage+="[I] ";
		break;
	case Log::VERBOSE:
		logMessage+="[V] ";
		break;
	default:
		break;
	}
	logMessage += tag + ": " + message;
	logQueue.push(logMessage);
}
