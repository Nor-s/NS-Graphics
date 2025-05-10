#include "logger.h"

namespace ns
{

std::shared_ptr<spdlog::logger> Logger::g_logger{nullptr};
std::string Logger::g_prefix{""};

Logger::Logger()
{
	std::vector<spdlog::sink_ptr> logSinks;
	logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(g_prefix + ".log", true));

	logSinks[0]->set_pattern("%^[%n][%H:%M:%S.%e --%L] %v%$ {%s::%! #%#}");
	logSinks[1]->set_pattern("[%n][%L][%H:%M:%S.%e] %v");

	g_logger = std::make_shared<spdlog::logger>(g_prefix, begin(logSinks), end(logSinks));
	spdlog::register_logger(g_logger);
	g_logger->set_level(spdlog::level::trace);
	g_logger->flush_on(spdlog::level::trace);
}

void Logger::SetLogPrefix(std::string_view prefix)
{
	g_prefix = prefix;
}

const std::shared_ptr<spdlog::logger>& Logger::getLogger() const
{
	return g_logger;
}

}	 // namespace sglib