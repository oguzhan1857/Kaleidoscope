#pragma once
#include <vector>


template <std::size_t Index, typename ReturnType, typename... Args>
__forceinline ReturnType call_virtual(void* instance, Args... args)
{
	using Fn = ReturnType(__thiscall*)(void*, Args...);
	auto function = (*reinterpret_cast<Fn**>(instance))[Index];
	return function(instance, args...);
}

#define __INT(ADDRESS)  static_cast<__int32>(ADDRESS)

#define __THIS(ADDRESS) (this + static_cast<__int32>(ADDRESS))

#define MAKE_GET(NAME, TYPE, CLASS) \
TYPE get_##NAME##() { \
	return *reinterpret_cast<TYPE*>(this + static_cast<__int32>(Offsets::##CLASS##::##NAME)); \
}

#define MAKE_GET_OFFSET(NAME, TYPE, OFFSET) \
TYPE get_##NAME##() { \
	return *reinterpret_cast<TYPE*>(this + OFFSET); \
}

#define MAKE_GET_PTR(NAME, TYPE, CLASS) \
TYPE get_##NAME##() { \
	return reinterpret_cast<TYPE>(this + static_cast<__int32>(Offsets::##CLASS##::##NAME)); \
}

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) uint8_t MACRO_CONCAT(_pad, __COUNTER__)[SIZE];