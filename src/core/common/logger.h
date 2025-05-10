#ifndef _NS_GRAPHICS_CORE_COMMONS_LOGGER_H_
#define _NS_GRAPHICS_CORE_COMMONS_LOGGER_H_

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "singleInstance.h"

#include <string>
#include <string_view>

namespace ns
{

class Logger : public SingleInstance<Logger>
{
	friend class SingleInstance<Logger>;
	static std::shared_ptr<spdlog::logger> g_logger;
	static std::string g_prefix;

private:
	Logger();

public:
	~Logger() = default;

	static void SetLogPrefix(std::string_view prefix);
	[[nodiscard]] const std::shared_ptr<spdlog::logger>& getLogger() const;
};

}	 // namespace ns

#define NS_INFO(...) SPDLOG_LOGGER_INFO(::ns::Logger::Get().getLogger(), __VA_ARGS__)
#define NS_ERROR(...) SPDLOG_LOGGER_ERROR(::ns::Logger::Get().getLogger(), __VA_ARGS__)
#define NS_WARN(...) SPDLOG_LOGGER_WARN(::ns::Logger::Get().getLogger(), __VA_ARGS__)
#define NS_LOG(...) SPDLOG_LOGGER_TRACE(::ns::Logger::Get().getLogger(), __VA_ARGS__)
#define NS_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(::ns::Logger::Get().getLogger(), __VA_ARGS__)

#endif	  // MINA_COMMONS_LOGGER_H