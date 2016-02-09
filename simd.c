#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stddef.h>
#include <immintrin.h>

#if (LUA_VERSION_NUM==501)
#define lua_len(L,i) (lua_pushnumber( (L), lua_objlen( (L), (i) )))
#define luaL_newlib(L,t) (luaL_register( (L), "simd", (t) ))
#endif

int luaopen_simd( lua_State *L );

struct lsimd_State {
	__v4sf xmm[8];	
} lsimd;

static int lsimd_extensions( lua_State *L ) {
	int count = 0;
#ifdef __MMX__ 
	lua_pushstring( L, "MMX" ); count++;
#endif
#ifdef __SSE__ 
	lua_pushstring( L, "SSE" ); count++;
#endif
#ifdef __SSE2__ 
	lua_pushstring( L, "SSE2" ); count++;
#endif
#ifdef __SSE3__ 
	lua_pushstring( L, "SSE3" ); count++;
#endif
#if defined (__SSE4_2__) || defined (__SSE4_1__)
	lua_pushstring( L, "SSE4" ); count++;
#endif
#ifdef __AVX__
	lua_pushstring( L, "AVX" ); count++;
#endif
#ifdef __AVX2__
	lua_pushstring( L, "AVX2" ); count++;
#endif
	return count;
}

static int lsimd_v4set( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	lsimd.xmm[i][0] = lua_tonumber( L, 2 );
	lsimd.xmm[i][1] = lua_tonumber( L, 3 );
	lsimd.xmm[i][2] = lua_tonumber( L, 4 );
	lsimd.xmm[i][3] = lua_tonumber( L, 5 );
	return 0;
}

static int lsimd_v4zeros( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	lsimd.xmm[i] = _mm_setzero_ps();
	return 0;
}

static int lsimd_v4tonumber( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	lua_pushnumber( L, lsimd.xmm[i][0] );
	lua_pushnumber( L, lsimd.xmm[i][1] );
	lua_pushnumber( L, lsimd.xmm[i][2] );
	lua_pushnumber( L, lsimd.xmm[i][3] );
	return 4;
}

static int lsimd_v4add( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	int j = luaL_checkint( L, 2 );
	int k = luaL_checkint( L, 3 );
	lsimd.xmm[k] = _mm_add_ps( lsimd.xmm[i], lsimd.xmm[j] );
	return 0;
}

static int lsimd_v4sub( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	int j = luaL_checkint( L, 2 );
	int k = luaL_checkint( L, 3 );
	lsimd.xmm[k] = _mm_sub_ps( lsimd.xmm[i], lsimd.xmm[j] );
	return 0;
}

static int lsimd_v4mul( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	int j = luaL_checkint( L, 2 );
	int k = luaL_checkint( L, 3 );
	lsimd.xmm[k] = _mm_mul_ps( lsimd.xmm[i], lsimd.xmm[j] );
	return 0;
}

static int lsimd_v4div( lua_State *L ) {
	int i = luaL_checkint( L, 1 );
	int j = luaL_checkint( L, 2 );
	int k = luaL_checkint( L, 3 );
	lsimd.xmm[k] = _mm_div_ps( lsimd.xmm[i], lsimd.xmm[j] );
	return 0;
}

static const luaL_Reg simdlib[] = {
	{"v4set", lsimd_v4set},
	{"v4zeros", lsimd_v4zeros},
	{"v4add", lsimd_v4add},
	{"v4sub", lsimd_v4sub},
	{"v4div", lsimd_v4div},
	{"v4mul", lsimd_v4mul},
	{"v4tonumber", lsimd_v4tonumber},
	{"extensions", lsimd_extensions },
	{NULL,NULL}
};

int luaopen_simd( lua_State *L ) {
	luaL_newlib( L, simdlib );
	return 1;
}
