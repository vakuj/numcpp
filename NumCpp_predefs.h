#include <cstdint>
#include "NumCpp.h"

/** Predefined data structures */

template <class T>
NumCpp<T> NumCpp<T>::zero(uint32_t *s_shape, uint32_t s_dims)
{
    NumCpp<T> ret;
    uint32_t s_size = _get_size(s_shape, s_dims);
    T *src = (T *)calloc(s_size, sizeof(T));
    ret.set(src, s_shape, s_dims);
    free(src);
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::fill(uint32_t *s_shape, uint32_t s_dims, const T val)
{
    NumCpp<T> ret = NumCpp<T>::zero(s_shape, s_dims);

    for (uint32_t i = 0; i < ret._size; ++i)
    {
        ret._insert(val, i);
    }
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::diag(uint32_t *s_shape, uint32_t s_dims)
{
    NumCpp<T> ret = zero(s_shape, s_dims);
    uint32_t min_shape = s_shape[0];
    if (s_dims == 1)
    {
        ret._insert((T)1, 0);
        return ret;
    }

    if (s_dims >= 2)
    {
        if (s_dims > 2)
            LOG(WARN, "no support for higher dims (s_dims > 2). setting only the first");
        if (s_shape[1] < min_shape)
            min_shape = s_shape[1];
    }
    for (uint32_t i = 0; i < min_shape; ++i)
    {
        ret._insert((T)1, i + i * s_shape[1]);
    }
    return ret;
}
