#include <cstdint>
#include "NumCpp.h"

/** N x N */
template <class T>
NumCpp<T> NumCpp<T>::zero(uint32_t n)
{
    NumCpp<T> ret;
    if (n == 0)
    {
        LOG(ERROR, "zero size data not possible");
        return ret;
    }
    ret._shape = (uint32_t *)calloc(2, sizeof(uint32_t));
    ret._shape[0] = n;
    ret._shape[1] = n;
    ret._dims = 2;
    ret._size = n * n;
    ret._data = (T *)calloc(ret._size, sizeof(T));
    return ret;
}
template <class T>
NumCpp<T> NumCpp<T>::diag(uint32_t n)
{
    NumCpp<T> ret = NumCpp<T>::zero(n);
    if (ret._data == NULL)
    {
        LOG(ERROR, "data is NULL, aborting here.");
        return ret;
    }
    for (uint32_t i = 0; i < n; ++i)
    {
        ret._insert((T)1, i + i * n);
    }
    return ret;
}
template <class T>
NumCpp<T> NumCpp<T>::fill(uint32_t n, const T val)
{
    NumCpp<T> ret = NumCpp<T>::zero(n);
    if (ret._data == NULL)
    {
        LOG(ERROR, "data is NULL, aborting here.");
        return ret;
    }
    for (uint32_t i = 0; i < ret._size; ++i)
    {
        ret._insert(val, i);
    }
    return ret;
}

/** 1 x N */

template <class T>
NumCpp<T> NumCpp<T>::arange(const T v0, const T v1, const T d, const bool end)
{
    NumCpp<T> ret;
    if (v1 == v0)
    {
        LOG(ERROR, "Start and end value cannot be the same (v1 = v0)");
        return ret;
    }
    if (d == 0)
    {
        LOG(ERROR, "Cannot make range with zero step length (d = 0)");
        return ret;
    }
    if (v1 > v0 && d < 0)
    {
        LOG(ERROR, "Negative step length while positive range (v0 > v1)");
        return ret;
    }
    ret._dims = 1;
    ret._shape = (uint32_t *)calloc(ret._dims, sizeof(uint32_t));
    if (end)
        ret._size = (uint32_t)((v1 + d - v0) / d);
    else
        ret._size = (uint32_t)((v1 - v0) / d);
    ret._shape[0] = ret._size;
    ret._data = (T *)calloc(ret._size, sizeof(T));

    T val = v0;
    for (uint32_t i = 0; i < ret._size; ++i)
    {
        ret._insert(val, i);
        val += d;
    }
    return ret;
}
template <class T>
NumCpp<T> NumCpp<T>::linspace(const T v0, const T v1, const uint32_t n)
{
    T d = 0;
    d = v1 - v0;
    d /= (T)n;
    return NumCpp<T>::arange(v0, v1, d, false);
}

/** M x N x ... */

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
