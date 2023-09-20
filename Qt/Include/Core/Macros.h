// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#pragma once

#include <QtGlobal>

#if defined(SHARED_LIBRARIES)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define CORE_EXPORT __declspec(dllexport)
#  else
#  define CORE_EXPORT __attribute__((__visibility__("default")))
#  endif
#else
#  define CORE_EXPORT
#endif

#define Stringify(x) #x
#define _Hashify(x) #x ## _hash
#define Hashify(x) _Hashify(x)

// Public domain by @Lee-R :: https://gist.github.com/Lee-R/3839813
inline constexpr quint32 fnv1a_32(char const *s, std::size_t count)
{
	return count ? (fnv1a_32(s, count - 1) ^ s[count - 1]) * 16777619u : 2166136261u;
}
constexpr quint32 operator"" _hash(char const* s, std::size_t count)
{
    return fnv1a_32(s, count);
}
//