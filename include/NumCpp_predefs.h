#include "NumCpp.h"

/** 1 x N */

/**
 * @brief Creates one dimensional data filled with values from v0
 *        to (and including) v1 with stepsize d.
 *        Failes if: (v1 == v0), (d == 0) or
 *        (v1 >  v0 && d < 0)
 *
 * @tparam T
 * @param v0 start value of range.
 * @param v1 end value of range.
 * @param d stepsize between values in range.
 * @param end if v1 is included in returnd data. (optional, default true)
 * @return NumCpp<T> the creaated 1D range. Empty data returned if failed to create range.
 */
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
/**
 * @brief Creates a one dimensional data filled with n equidistant
 *        between half open range v0 to v1.
 *        Calls arange(), see for fail conditions
 *
 * @tparam T
 * @param v0 start value of range
 * @param v1 end value of range (not included)
 * @param n number of values in range
 * @return NumCpp<T> the created 1D range. Empty data returned if failed to create range.
 */
template <class T>
NumCpp<T> NumCpp<T>::linspace(const T v0, const T v1, const uint32_t n)
{
    T d = 0;
    d = v1 - v0;
    d /= (T)n;
    return NumCpp<T>::arange(v0, v1, d, false);
}

/** N x N */

/**
 * @brief Creates n x n data filled with zeros. Failes if n == 0.
 *
 * @tparam T
 * @param n the n size
 * @return NumCpp<T> the created n x n data. Empty data if failed.
 */
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

/**
 * @brief Creates n x n data filled with zeros except on the diagonal where
 *        ones are inserted. Failes if n == 0.
 *
 * @tparam T
 * @param n the n size
 * @return NumCpp<T> the created n x n data. Empty data if failed.
 */
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

/**
 * @brief Creates n x n data filled with val. Failes if n == 0.
 *
 * @tparam T
 * @param n the n size
 * @param val the value to fill with
 * @return NumCpp<T> the created n x n data. Empty data if failed.
 */
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

/** M x N */

/**
 * @brief Creates m x n data filled with zeros. Failes if m == 0 && n == 0.
 *
 * @tparam T
 * @param m the m size
 * @param n the n size
 * @return NumCpp<T> the created m x n data. Empty data if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::zero(uint32_t m, uint32_t n)
{
    NumCpp<T> ret;
    if (m == 0 && n == 0)
    {
        LOG(ERROR, "Zero size data not possible, (m x n = 0 x 0)");
        return ret;
    }
    if (m == 0 && n > 0)
    {
        LOG(ERROR, "Zero on first dim not possible,  (m x n = 0 x n)");
        return ret;
    }
    if (m >= 1 && n == 0)
    {
        ret._dims = 1;
        ret._shape = (uint32_t *)calloc(ret._dims, sizeof(uint32_t));
        ret._shape[0] = m;
        ret._size = m;
        ret._data = (T *)calloc(ret._size, sizeof(T));
        return ret;
    }
    ret._dims = 2;
    ret._shape = (uint32_t *)calloc(ret._dims, sizeof(uint32_t));
    ret._shape[0] = m;
    ret._shape[1] = n;
    ret._size = m * n;
    ret._data = (T *)calloc(ret._size, sizeof(T));
    return ret;
}

/**
 * @brief Creates m x n data filled with zeros except on the shortes diagonal
 *        where ones are inserted. Failes if m == 0 && n == 0.
 *
 * @tparam T
 * @param m the m size
 * @param n the n size
 * @return NumCpp<T> the created m x n data. Empty data if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::diag(uint32_t m, uint32_t n)
{

    NumCpp<T> ret = NumCpp<T>::zero(m, n);
    if (ret._data == NULL)
    {
        LOG(ERROR, "data is NULL, aborting here");
        return ret;
    }
    uint32_t min_size = 0;
    if (ret._dims == 1)
    {
        ret._insert((T)1, 0);
        return ret;
    }
    else
    {
        min_size = (ret._shape[0] < ret._shape[1]) ? ret._shape[0] : ret._shape[1];
    }
    for (uint32_t i = 0; i < min_size; ++i)
    {
        ret._insert((T)1, i + i * ret._shape[1]);
    }
    return ret;
}

/**
 * @brief Creates m x n data filled with val. Failes if m == 0 && n == 0.
 *
 * @tparam T
 * @param m the m size
 * @param n the n size
 * @param val the value to fill with
 * @return NumCpp<T> the created m x n data. Empty data if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::fill(uint32_t m, uint32_t n, const T val)
{
    NumCpp<T> ret = NumCpp<T>::zero(m, n);
    if (ret._data == NULL)
    {
        LOG(ERROR, "data is NULL, aborting here");
        return ret;
    }
    for (uint32_t i = 0; i < ret._size; ++i)
    {
        ret._insert(val, i);
    }
    return ret;
}

/** M x N x ... */

/**
 * @brief Create n-dimensional data specified by s_shape and s_dims filled with zeros.
 *
 * @tparam T
 * @param s_shape the target shape
 * @param s_dims the target dim, i.e. number of elements in s_shape
 * @return NumCpp<T> the created n-dimensional data
 */
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
/**
 * @brief Create n-dimensional data specified by s_shape and s_dims filled with val.
 *
 * @tparam T
 * @param s_shape the target shape
 * @param s_dims the target dim, i.e. number of elements in s_shape
 * @param val the value to fill the data with
 * @return NumCpp<T> the created n-dimensional data
 */
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
