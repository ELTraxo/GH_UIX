#pragma once
#include "stdafx.h"

#define sq(n) n*n

#include "misc\vec2.h"
#include "misc\vec3.h"
#include "misc\vec4.h"

#ifdef UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif

using uint = unsigned int;
using vec2ui = vec2<uint>;
using vec2i = vec2<int>;
using vec2f = vec2<float>;
using vec3f = vec3<float>;
using vec4f = vec4<float>;