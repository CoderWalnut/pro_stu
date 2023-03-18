#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <stdint.h>
#include <string.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include <map>
#include "util.h"
#include "singleton.h"
#include "thread.h"


namespace sylar {

class Logger;
class LoggerManager;

class LogLevel {
public:
    enum Level {
    	UNKNOW = 0;
		DEBUG  = 1;
		INFO   = 2;
		WARN   = 3;
		ERROR  = 4;
		FATAL  = 5;
    };

	static const char* ToString(LogLevel::Level level);

	static LogLevel::Level FromString(const std::string& str);
};

class LogEvent {
public:
	typedef std::shared_ptr<LogEvent> ptr;

	LogEvent(const char* file, uint32_t line, uint64_t elapse, uint32_t threadId
			, uint32_t fiberId, uint64_t time, std::string& threadName
			, std::shared_ptr<Logger> logger, LogLevel::Level level);

	const char* getFile() const { return m_file; }

	uint32_t getLine() const { return m_line; }

	uint64_t getElapse() const { return m_elapse; }

	uint32_t getThreadId() const { return m_threadId; }

	uint32_t getFiberId() const { return m_fiberId; }

	uint64_t getTime() const { return m_time; }

	std::string& getThreadName() { return m_threadName; }

	std::string getContent() const { return m_ss.str(); }

	std::stringstream& getSS() { return m_ss; }

	std::shared_ptr<Logger> getLogger() { return m_logger; }

	LogLevel::Level getLevel() { return m_level; }

	void format(const char* fmt, va_list al);

	void format(const char* fmt,...);

private:
	//文件名
	const char* m_file = nullptr;
	//行号
	uint32_t m_line = 0;
	//程序启动开始到现在的毫秒数
	uint64_t m_elapse = 0;
	//线程ID
	uint32_t m_threadId = 0;
	//协程ID
	uint32_t m_fiberId = 0;
	//时间戳
	uint64_t m_time;
	//线程名称
	std::string m_threadName;
	//日志内容流
	std::stringstream m_ss;
	//日志器
	std::shared_ptr<Logger> m_logger;
	//日志级别
	LogLevel::Level m_level;
};

class LogEventWrap {
public:
	LogEventWrap(LogEvent::ptr event);

	~LogEventWrap();

	LogEvent::ptr getEvent() const { return m_event }

	std::stringstream& getSS();

private:
	//日志事件
	LogEvent::ptr m_ event;
};

class LogFormatter {
public:
	typedef std::shared_ptr<LogFormatter> ptr;

	class FormatItem {
	public:
		typedef std::shared_ptr<FormatItem> ptr;

		virtual ~FormatItem() {}

		virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
	};

	void init();

	bool isError() const { return m_error; }

	std::string getPattern() const { return m_pattern; }
	
private:
	//日志格式模版
	std::string m_pattern;
	//日志格式模版解析结果
	std::vector<FormatItem> m_items;
	//是否有错误
	bool m_error;

};

class LogAppender {
friend class Logger;
public:
	typedef std::shared_ptr<LogAppender> ptr;
	typedef Spinlock MutexType;

	virtual ~LogAppender() {}

	virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

	virtual std::string toYamlString() = 0;

	void setFormatter(LogFormatter::ptr val);

	LogFormatter::ptr getFormatter();

	LogLevel::Level getLevel() const { return m_level; }

	void setLevel(LogLevel::Level val) { m_level = val; }

protected:
	//日志级别
	LogLevel::Level m_level = LogLevel::DEBUG;
	//是否有自己的日志格式器
	bool m-hasFormatter = false;
	//日志格式器
	LogFormatter::ptr m_formatter;
};

class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;

public:
	typedef std::shared_ptr<Logger> ptr;
	typedef Spinlock MutexType;

	Logger(const std::string& name = "root");

	void log(LogLevel::Level level, LogEvent::ptr event);

	void debug(LogEvent::ptr event);

	void info(LogEvent::ptr event);
	
	void warn(LogEvent::ptr event);

	void error(LogEvent::ptr event);
	
	void fatal(LogEvent::ptr event);

	void addAppender(LogAppender::ptr appender);

	void delAppender(LogAppender::ptr appender);

	void clearAppender();

	LogLevel::Level getLevel() const { return m_level; }

	void setLevel(LogLevel::Level val) { m_level = val; } 

	const std::string& getName() const { return m_name; }

	void setFormatter(LogFormatter::ptr val);

	void setFormatter(const std::string& val);

	LogFormatter::ptr getFormatter();

	std::string toYamlString();

private:
	//日志名称
	std::string m_name;
	//日志级别
	LogLevel::Level m_level;
	//Mutex
	MutexType m_mutex;
	//日志目标集合
	std::list<LogAppender::ptr> m_appenders;
	//日志格式器
	LogFormatter::ptr m_formatter;
	//主日志器
	Logger::ptr m_root;
}

class StdoutLogAppender : public LogAppender {
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
	void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
	std::string toYamlString() override;
};

class FileLogAppender : public LogAppender {
public:
	typedef std::shared_ptr<FileLogAppender> ptr;
	FileLogAppender(const std::string& filename);
	void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
	std::string toYamlString() override;
	bool reopen();

private:
	//文件路径
	std::string m_filename;
	//文件流
	std::ofstream m_filestream;
	//上次重新打开时间
	uint64_t m_lastTime = 0;
};

class LoggerManager {
public:
	typedef Spinlock MutexType;

	LoggerManager();

	Logger::ptr getLogger(const std::string& name);

	void init();

	Logger::ptr getRoot() const { return m_root; }

	std::string toYamlString();

private:
	//Mutex
	MutexType m_mutex;
	//日志器容器
	std::map<std::string, Logger::ptr> m_loggers;
	//主日志器
	Logger::ptr m_root;	
};

typedef sylar::Singleton<LoggerManager> LoggerMgr;

}

#endif
