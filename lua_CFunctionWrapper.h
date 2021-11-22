#pragma once

#include <string>
#include "lua.h"
#include "lualib.h"




#define lua_CFunctionWrapper(FUN)  &lua_CFunctionWrapperStruct<decltype(FUN), FUN>::function

#define lua_CFunctionWrapper_PushValue(val) { \
	if constexpr (std::is_same<decltype(val), bool>::value) \
		lua_pushboolean(L, val); \
	else if constexpr (std::is_same<decltype(val), std::string>::value) \
		lua_pushstring(L, val.c_str()); \
	else if constexpr (std::is_arithmetic<decltype(val)>::value) \
		lua_pushnumber(L, val); \
	else \
		static_assert(false, "not supported"); \
}

#define lua_CFunctionWrapper_PopArg(TYPE, i)  \
	TYPE a##i; \
	if constexpr (std::is_same<TYPE, bool>::value) \
		a##i = luaL_checkboolean(L, i); \
	else if constexpr (std::is_same<TYPE, std::string>::value) \
		a##i = luaL_checkstring(L, i); \
	else if constexpr (std::is_arithmetic<TYPE>::value) \
		a##i = static_cast<TYPE>(luaL_checknumber(L, i)); \
	else \
		static_assert(false, "not supported"); \


template<typename Sig, Sig& S>
struct lua_CFunctionWrapperStruct;

template<typename Ret, Ret(&P)()>
struct lua_CFunctionWrapperStruct<Ret(), P>
{
	int	static function(lua_State* L)
	{
		if constexpr (std::is_void<Ret>::value)
		{
			P();

			return 0;
		}
		else
		{
			Ret result = P();

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, Ret(&P)(T1)>
struct lua_CFunctionWrapperStruct<Ret(T1), P> 
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1);

			return 0;
		}
		else
		{
			Ret result = P(a1);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};


template<typename Ret, typename T1, typename T2, Ret(&P)(T1,T2)>
struct lua_CFunctionWrapperStruct<Ret(T1,T2), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, Ret(&P)(T1, T2, T3)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, Ret(&P)(T1, T2, T3, T4)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, Ret(&P)(T1, T2, T3, T4, T5)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, Ret(&P)(T1, T2, T3, T4, T5, T6)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5, T6), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);
		lua_CFunctionWrapper_PopArg(T6, 6);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5, a6);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5, a6);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, Ret(&P)(T1, T2, T3, T4, T5, T6, T7)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5, T6, T7), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);
		lua_CFunctionWrapper_PopArg(T6, 6);
		lua_CFunctionWrapper_PopArg(T7, 7);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5, a6, a7);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5, a6, a7);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, Ret(&P)(T1, T2, T3, T4, T5, T6, T7, T8)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5, T6, T7, T8), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);
		lua_CFunctionWrapper_PopArg(T6, 6);
		lua_CFunctionWrapper_PopArg(T7, 7);
		lua_CFunctionWrapper_PopArg(T8, 8);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5, a6, a7, a8);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5, a6, a7, a8);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, Ret(&P)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5, T6, T7, T8, T9), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);
		lua_CFunctionWrapper_PopArg(T6, 6);
		lua_CFunctionWrapper_PopArg(T7, 7);
		lua_CFunctionWrapper_PopArg(T8, 8);
		lua_CFunctionWrapper_PopArg(T9, 9);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5, a6, a7, a8, a9);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5, a6, a7, a8, a9);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};

template<typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, Ret(&P)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
struct lua_CFunctionWrapperStruct<Ret(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10), P>
{
	int	static function(lua_State* L)
	{
		lua_CFunctionWrapper_PopArg(T1, 1);
		lua_CFunctionWrapper_PopArg(T2, 2);
		lua_CFunctionWrapper_PopArg(T3, 3);
		lua_CFunctionWrapper_PopArg(T4, 4);
		lua_CFunctionWrapper_PopArg(T5, 5);
		lua_CFunctionWrapper_PopArg(T6, 6);
		lua_CFunctionWrapper_PopArg(T7, 7);
		lua_CFunctionWrapper_PopArg(T8, 8);
		lua_CFunctionWrapper_PopArg(T9, 9);
		lua_CFunctionWrapper_PopArg(T10, 10);

		if constexpr (std::is_void<Ret>::value)
		{
			P(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

			return 0;
		}
		else
		{
			Ret result = P(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);

			lua_CFunctionWrapper_PushValue(result);

			return 1;
		}
	}
};


#undef CFunctionWrapper_PushValue
#undef CFunctionWrapper_PopArg



