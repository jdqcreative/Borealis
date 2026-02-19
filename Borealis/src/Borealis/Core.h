#pragma once

#ifdef BO_ENABLE_ASSERTS
	#define BO_ASSERT(x, ...) { if(!(x)) { BO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BO_CORE_ASSERT(x, ...) { if(!(x)) { BO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BO_ASSERT(x, ...)
	#define BO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)