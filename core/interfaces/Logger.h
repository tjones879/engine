#ifndef LOGGER_H
#define LOGGER_H

#include "../structs/ConcurrentQueue.h"
#include <mutex>
#include <string>

namespace Log {
	enum LogChannel
	{
		ERROR,DEBUG,INFO,VERBOSE,SHADER
	};
}

class Logger
{
public:
	Logger(const std::string logFile);
	void write();
	void addMessage(Log::LogChannel channel, std::string tag, std::string message);
private:
	ConcurrentQueue<std::string> logQueue;
	std::string filePath;
	std::mutex fileMutex;
};

#endif // !LOGGER_H

