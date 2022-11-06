#include "NumCpp.h"
#include <cassert>

template <class T>
bool NumCpp<T>::assert_shape(const NumCpp<T> self, const NumCpp<T> ref)
{
    if (!assert_dims(self, ref))
        return false;
    for (uint32_t i = 0; i < self._dims; ++i)
    {
        if (self._shape[i] != ref._shape[i])
            return false;
    }
    return true;
}
template <class T>
bool NumCpp<T>::assert_memory(const NumCpp<T> self, const NumCpp<T> ref)
{
    if (assert_empty(self))
        return false;
    if (assert_empty(ref))
        return false;
    if (!assert_size(self, ref))
        return false;

    for (uint32_t i = 0; i < self._size; ++i)
    {
        if (self._data[i] != ref._data[i])
            return false;
    }
    return true;
}
template <class T>
void NumCpp<T>::assert_check(bool expr, const char *file, const char *func, int line, const char *msg)
{
    if (!expr)
    {
        printf("[Assertion failed] %s:%s:%03d: %s\n", file, func, line, msg);
        // abort();
    }
    else
        printf("[Assertion passed] %s:%s:%03d\n", file, func, line);
}

#define ASSERT_SIZE(_self, _ref) NumCpp<float>::assert_check(NumCpp<float>::assert_size(_self, _ref), __FILE__, __FUNCTION__, __LINE__, "_size must match")
#define ASSERT_DIMS(_self, _ref) NumCpp<float>::assert_check(NumCpp<float>::assert_dims(_self, _ref), __FILE__, __FUNCTION__, __LINE__, "_dims must match")
#define ASSERT_SHAPE(_self, _ref) NumCpp<float>::assert_check(NumCpp<float>::assert_shape(_self, _ref), __FILE__, __FUNCTION__, __LINE__, "_shape must match")
#define ASSERT_MEMORY(_self, _ref) NumCpp<float>::assert_check(NumCpp<float>::assert_memory(_self, _ref), __FILE__, __FUNCTION__, __LINE__, "_data must match")

#define ASSERT_EMPTY(_self) NumCpp<float>::assert_check(NumCpp<float>::assert_empty(_self), __FILE__, __FUNCTION__, __LINE__, "_data must be empty")