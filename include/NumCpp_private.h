
#include "NumCpp.h"

/** [PRIVATE] */

template <class T>
inline uint32_t NumCpp<T>::_index(loc_t loc)
{
    return ((loc.col + loc.row * this->_shape[1]) % this->_size);
}
template <class T>
inline uint32_t NumCpp<T>::_col_nbr(uint32_t index)
{
    return ((index % this->_shape[0]));
}
template <class T>
inline uint32_t NumCpp<T>::_row_nbr(uint32_t index)
{
    return (this->_dims < 2) ? 0 : ((index / this->_shape[0]) % (this->_shape[0] * this->_shape[1]));
}
template <class T>
inline uint32_t NumCpp<T>::_page_nbr(uint32_t index)
{
    /** TODO */
    // return (this->_dims < 3) ? 0 : ((index / this->_shape[0]) % (this->_shape[0] * this->_shape[1]));
    return 0;
}

template <class T>
inline T NumCpp<T>::_get_row_element(uint32_t row_index, uint32_t offset)
{
    return this->_data[this->_index({row_index, offset})];
}
template <class T>
inline T NumCpp<T>::_get_col_element(uint32_t col_index, uint32_t offset)
{
    return this->_data[this->_index({offset, col_index})];
}
template <class T>
inline T NumCpp<T>::_get_diag_element(uint32_t diag_index, uint32_t offset)
{
    return this->_data[this->_index({diag_index + offset, diag_index + offset})];
}

template <class T>
T *NumCpp<T>::_get_col(T *dst, uint32_t offset)
{
    if (dst == NULL)
        dst = (T *)calloc(this->_shape[1], sizeof(T));
    loc_t loc = {0, 0};
    for (uint32_t i = 0; i < this->_shape[1]; ++i)
    {
        loc.row = i;
        loc.col = offset;
        dst[i] = this->_data[this->_index(loc)];
    }
    return dst;
}
template <class T>
T *NumCpp<T>::_get_row(T *dst, uint32_t offset)
{
    if (dst == NULL)
        dst = (T *)calloc(this->_shape[0], sizeof(T));
    loc_t loc = {0, 0};
    for (uint32_t i = 0; i < this->_shape[0]; ++i)
    {
        loc.row = offset;
        loc.col = i;
        dst[i] = this->_data[this->_index(loc)];
    }
    return dst;
}
template <class T>
T *NumCpp<T>::_get_diag(T *dst, uint32_t offset)
{
    uint32_t min_shape = this->_shape[0] <= this->_shape[1] ? this->_shape[0] : this->_shape[1];
    if (dst == NULL)
        dst = (T *)calloc(min_shape, sizeof(T));
    loc_t loc = {0, 0};
    for (uint32_t i = 0; i < min_shape; ++i)
    {
        loc.row = (i + offset) % min_shape;
        loc.col = (i + offset) % min_shape;
        dst[i] = this->_data[this->_index(loc)];
    }
    return dst;
}
template <class T>
T *NumCpp<T>::_get_page(T *dst, uint32_t offset)
{
    if (dst == NULL)
        dst = (T *)calloc(this->_shape[0] * this->_shape[1], sizeof(T));
    /** TODO */
    return dst;
}

/**
 * @brief Calculated the size of data for given shape
 *
 * @tparam T
 * @param s_shape shape of data to use for size calculation
 * @param s_dims number of elements in s_dims
 * @return uint32_t the size (> 0) of data. 0 if failed.
 */
template <class T>
uint32_t NumCpp<T>::_get_size(const uint32_t *s_shape, uint32_t s_dims)
{
    if (s_shape == NULL)
    {
        LOG(ERROR, "Cannot calculate size of NULL shape");
        return 0;
    }
    if (s_dims == 0)
    {
        LOG(ERROR, "Cannot calculate size of 0 dims");
        return 0;
    }
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
    }
    return s_size;
}
/**
 * @brief Updates the shape of data by flattening to single dimension
 *
 * @tparam T
 * @param s_size size of the data.
 */
template <class T>
void NumCpp<T>::_upd_shape(const uint32_t s_size)
{

    if (this->_shape == NULL)
    {
        this->_shape = (uint32_t *)malloc(sizeof(uint32_t));
    }
    else
    {
        if (this->_dims != 1)
        {
            this->_shape = (uint32_t *)realloc(this->_shape, 1 * sizeof(uint32_t));
        }
    }
    this->_shape[0] = s_size;
    this->_dims = 1;
    this->_size = s_size;
}
/**
 * @brief Updates the shape according to s_shape and s_dims.
 *
 * @tparam T
 * @param s_shape the new shape
 * @param s_dims the new number of dimensions
 */
template <class T>
void NumCpp<T>::_upd_shape(const uint32_t *s_shape, uint32_t s_dims)
{
    if (this->_shape == NULL)
    {
        this->_shape = (uint32_t *)malloc(s_dims * sizeof(uint32_t));
    }
    else
    {
        if (s_dims != this->_dims)
        {
            this->_shape = (uint32_t *)realloc(this->_shape, s_dims * sizeof(uint32_t));
        }
    }

    this->_shape = (uint32_t *)memcpy(this->_shape, s_shape, s_dims * sizeof(uint32_t));
    this->_dims = s_dims;
    this->_size = 1;
    for (uint32_t i = 0; i < this->_dims; i++)
    {
        this->_size *= this->_shape[i];
    }
}

/**
 * @brief Checks if location is inside bounds of data.
 *        dims != 2 not suppoerted
 *
 * @tparam T
 * @param loc the location to check
 * @return false if outside of bounds
 */
template <class T>
bool NumCpp<T>::_inside_bound(const loc_t loc)
{
    if (this->_dims != 2)
        return false;
    if (loc.row > this->_shape[0] || loc.col > this->_shape[1])
        return false;
    return this->_inside_bound(loc.row * this->_shape[1] + loc.col);
}
/**
 * @brief Checks if location is inside bounds of data.
 *
 * @tparam T
 * @param s_loc n-dimensional location
 * @param s_dims the amount of element sin s_loc
 * @return false if outside of bounds.
 */
template <class T>
bool NumCpp<T>::_inside_bound(const uint32_t *s_loc, const uint32_t s_dims)
{
    if (s_dims != this->_dims)
        return false;
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_loc[i];
        if (s_loc[i] > this->_shape[i])
            return false;
    }
    return this->_inside_bound(s_size);
}

/**
 * @brief Inserts val at offset.
 *        Does nothing if offset is outside of bounds.
 *
 * @tparam T
 * @param val value to insert
 * @param offset at location to insert, i.e. < size
 */
template <class T>
void NumCpp<T>::_insert(T val, uint32_t offset)
{
    if (offset < this->_size)
    {
        this->_data[offset] = val;
        return;
    }
    LOG(ERROR, "Attempt at insertion outside allowed memory");
    LOG(INFO, "Insertion aborted");
}

/**
 * @brief Checks if shape is the same as for other
 *
 * @tparam T
 * @param other the one to compare to
 * @return true if shapes are the same
 */
template <class T>
bool NumCpp<T>::_check_shape(const NumCpp<T> *other)
{
    if (this->_dims != other->_dims)
        return false;
    for (uint32_t i = 0; i < this->_dims; ++i)
    {
        if (this->_shape[i] != other->_shape[i])
            return false;
    }
    return true;
}
/**
 * @brief Applies each element of this with constant other using fun.
 *        Inserts the result of fun in returned data.
 *
 * @tparam T
 * @param other the second value for fun
 * @param fun pointer to function with two arguments (T, T) and returns T
 * @return NumCpp<T> the returned data. Unmodified this is returned if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::_op_cfun(const T other, T (*fun)(T, T))
{
    if (!this->_check_null())
    {
        LOG(WARN, "Null check failed on this");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], other), i);
    }
    return ret;
}
/**
 * @brief Applies each element of this with correspondig element from other using fun.
 *        Inserts the result of fun in returned data.
 *
 * @tparam T
 * @param other the source of second argument values for fun
 * @param fun pointer to function with two arguments (T, T) and returns T
 * @return NumCpp<T> the returned data. Unmodified this is returned if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::_op_nfun(const NumCpp<T> &other, T (*fun)(T, T))
{
    if (!this->_check_null())
    {
        LOG(WARN, "Null check failed on this");
        return *this;
    }
    if (!_check_null(other._data, other._shape, other._dims))
    {
        LOG(WARN, "Null check failed on other");
        return *this;
    }
    if (!this->_check_shape(&other))
    {
        LOG(WARN, "Incompatible shapes for this and other");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], other._data[i]), i);
    }
    return ret;
}
/**
 * @brief Pre-allocated version of _op_nfun(). Requires
 *        dst to be allocated before call. Does not modify content
 *        at dst if failed at any point.
 *
 * @tparam T
 * @param dst the destination where to insert result of fun
 * @param a the source of first argument to fun
 * @param b the source of second argument to fun
 * @param fun pointer to function with two arguments (T, T) and returns T
 * @return NumCpp<T>* the same pointer as dst
 */
template <class T>
NumCpp<T> *NumCpp<T>::_pre_op_nfun(NumCpp<T> *dst, NumCpp<T> *a, NumCpp<T> *b, T (*fun)(T, T))
{
    if (!dst->_check_null() || !a->_check_null() || !b->_check_null())
    {
        LOG(WARN, "Null Check failed for at least one of dst, a or b");
        return dst;
    }
    if (!dst->_check_shape(a) || !a->_check_shape(b))
    {
        LOG(WARN, "Shapes of dst, a and/or b not equal");
        return dst;
    }
    for (uint32_t i = 0; i < dst->_size; ++i)
    {
        dst->_insert(fun(a->_data[i], b->_data[i]), i);
    }
    return dst;
}
/**
 * @brief Pre-allocated version of _op_cfun(). Requires
 *        dst to be allocated before call. Does not modify content
 *        at dst if failed at any point.
 *
 * @tparam T
 * @param dst the destination where to insert result of fun
 * @param a the source of first argument to fun
 * @param b the source of second argument to fun
 * @param fun pointer to function with two arguments (T, T) and returns T
 * @return NumCpp<T>* the same pointer as dst
 */
template <class T>
NumCpp<T> *NumCpp<T>::_pre_op_cfun(NumCpp<T> *dst, NumCpp<T> *a, const T b, T (*fun)(T, T))
{
    if (!dst->_check_null() || !a->_check_null())
    {
        LOG(WARN, "Null Check failed for at least one of dst or a");
        return dst;
    }
    if (!dst->_check_shape(a))
    {
        LOG(WARN, "Shapes of dst and a not equal");
        return dst;
    }
    for (uint32_t i = 0; i < dst->_size; ++i)
    {
        dst->_insert(fun(a->_data[i], b), i);
    }
    return dst;
}

/**
 * @brief Applies each element of this with constant other using fun.
 *        Inserts the result of fun in returned data, as T equivalent of
 *        1 (true) and 0 (false).
 *
 * @tparam T
 * @param other the second value of to function fun
 * @param fun pointer to function with two arguments (T, T) and returns bool
 * @return NumCpp<T> the returned data. Unmodified this is returned if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::_op_clogic(const T other, bool (*fun)(T, T))
{
    if (!this->_check_null())
    {
        LOG(WARN, "Null check failed on this");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], other) ? (T)1 : (T)0, i);
    }
    return ret;
}

/**
 * @brief Applies each element of this with correspondig element from other using fun.
 *        Inserts the result of fun in returned data, as T equivalent of
 *        1 (true) and 0 (false).
 *
 * @tparam T
 * @param other the source of second argument values for fun
 * @param fun pointer to function with two arguments (T, T) and returns bool
 * @return NumCpp<T> the returned data. Unmodified this is returned if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::_op_nlogic(const NumCpp<T> &other, bool (*fun)(T, T))
{
    if (!this->_check_null())
    {
        LOG(WARN, "Null check failed on this");
        return *this;
    }
    if (!_check_null(other._data, other._shape, other._dims))
    {
        LOG(WARN, "Null check failed on other");
        return *this;
    }
    if (!_check_shape(&other))
    {
        LOG(WARN, "Incompatible shapes for this and other");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], other._data[i]) ? (T)1 : (T)0, i);
    }
    return ret;
}

/**
 * @brief Pre-allocated version of _op_nlogix(). Requires
 *        dst to be allocated before call. Does not modify content
 *        at dst if failed at any point.
 *
 * @tparam T
 * @param dst the destination where to insert result of fun
 * @param a the source of first argument to fun
 * @param b the source of second argument to fun
 * @param fun pointer to function with two arguments (T, T) and returns bool
 * @return NumCpp<T>* the same pointer as dst
 */
template <class T>
NumCpp<T> *NumCpp<T>::_pre_op_nlogic(NumCpp<T> *dst, NumCpp<T> *a, NumCpp<T> *b, bool (*fun)(T, T))
{
    if (!dst->_check_null() || !a->_check_null() || !b->_check_null())
    {
        LOG(WARN, "Null Check failed for at least one of dst, a or b");
        return dst;
    }
    if (!dst->_check_shape(a) || !a->_check_shape(b))
    {
        LOG(WARN, "Shapes of dst, a and/or b not equal");
        return dst;
    }
    for (uint32_t i = 0; i < dst->_size; ++i)
    {
        dst->_insert(fun(a->_data[i], b->_data[i]) ? (T)1 : (T)0, i);
    }
    return dst;
}

/**
 * @brief Pre-allocated version of _op_clogic(). Requires
 *        dst to be allocated before call. Does not modify content
 *        at dst if failed at any point.
 *
 * @tparam T
 * @param dst the destination where to insert result of fun
 * @param a the source of first argument to fun
 * @param b the source of second argument to fun
 * @param fun pointer to function with two arguments (T, T) and returns bool
 * @return NumCpp<T>* the same pointer as dst
 */
template <class T>
NumCpp<T> *NumCpp<T>::_pre_op_clogic(NumCpp<T> *dst, NumCpp<T> *a, const T b, bool (*fun)(T, T))
{
    if (!dst->_check_null() || !a->_check_null())
    {
        LOG(WARN, "Null Check failed for at least one of dst or a");
        return dst;
    }
    if (!dst->_check_shape(a))
    {
        LOG(WARN, "Shapes of dst and a not equal");
        return dst;
    }
    for (uint32_t i = 0; i < dst->_size; ++i)
    {
        dst->_insert(fun(a->_data[i], b) ? (T)1 : (T)0, i);
    }
    return dst;
}
