#pragma once

#include "spdlog/spdlog.h"

namespace Borealis {

	class Log
	{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define BO_CORE_TRACE(...)	::Borealis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BO_CORE_INFO(...)	::Borealis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BO_CORE_WARN(...)	::Borealis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BO_CORE_ERROR(...)	::Borealis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BO_CORE_FATAL(...)	::Borealis::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BO_TRACE(...)	::Borealis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BO_INFO(...)	::Borealis::Log::GetClientLogger()->info(__VA_ARGS__)
#define BO_WARN(...)	::Borealis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BO_ERROR(...)	::Borealis::Log::GetClientLogger()->error(__VA_ARGS__)
#define BO_FATAL(...)	::Borealis::Log::GetClientLogger()->fatal(__VA_ARGS__)