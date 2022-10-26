
#include "NumCpp.h"

/** [PRIVATE] */
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

template <class T>
bool NumCpp<T>::_inside_bound(const uint32_t loc)
{
    return loc < this->_size;
}
template <class T>
bool NumCpp<T>::_inside_bound(const loc_t loc)
{
    if (this->_dims != 2)
        return false;
    if (loc.row > this->_shape[1] || loc.col > this->_shape[0])
        return false;
    return this->_inside_bound(loc.row * this->_shape[0] + loc.col);
}
template <class T>
bool NumCpp<T>::_inside_bound(const uint32_t *s_shape, const uint32_t s_dims)
{
    if (s_dims != this->_dims)
        return false;
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
        if (s_shape[i] > this->_shape[i])
            return false;
    }
    return this->_inside_bound(s_size);
}

template <class T>
bool NumCpp<T>::_set_data(const T *src, const uint32_t *s_shape, uint32_t s_dims)
{
    uint32_t s_size = _get_size(s_shape, s_dims);
    if (this->_data == NULL)
    {
        this->_data = (T *)calloc(s_size, sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
        return this->_data != NULL;
    }
    else if (this->_size != s_size)
    {
        this->_data = (T *)realloc(this->_data, s_size * sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
        return this->_data != NULL;
    }
    else if (this->_size == s_size)
    {
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
        return this->_data != NULL;
    }
    else
        LOG(IMPL, "Not implemented yet --> Uncatched case for setting data encountered");
    return false;
}

template <class T>
void NumCpp<T>::_insert(T val, uint32_t offset)
{
    if (offset > this->_size)
    {
        LOG(ERROR, "Attempt at insertion outside allowed memory");
        LOG(INFO, "Insertion aborted");
        return;
    }
    this->_data[offset] = val;
}

template <class T>
bool NumCpp<T>::_check_null(void)
{
    return (this->_data != NULL && this->_shape != NULL && this->_dims != 0);
}
template <class T>
bool NumCpp<T>::_check_null(const T *src, uint32_t *shape, uint32_t dims)
{
    return (src != NULL && shape != NULL && dims != 0);
}

template <class T>
bool NumCpp<T>::_check_shape(const NumCpp<T> *b)
{
    if (this->_dims != b->_dims)
        return false;
    // uint32_t *ash = a->shape();
    // const uint32_t *bsh = b->shape();
    for (uint32_t i = 0; i < this->_dims; ++i)
    {
        if (this->_shape[i] != b->_shape[i])
            return false;
    }
    return true;
}

template <class T>
NumCpp<T> NumCpp<T>::_op_cfun(const T b, T (*fun)(T, T))
{

    // if (!_check_null(this->_data, this->_shape, this->_dims))
    if (!this->_check_null())
    {
        LOG(WARN, "Null check failed on a");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], b), i);
    }
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::_op_nfun(const NumCpp<T> &b, T (*fun)(T, T))
{
    if (!_check_null(this->_data, this->_shape, this->_dims))
    {
        LOG(WARN, "Null check failed on a");
        return *this;
    }
    if (!_check_null(b._data, b._shape, b._dims))
    {
        LOG(WARN, "Null check failed on b");
        return *this;
    }
    if (!_check_shape(&b))
    {
        LOG(WARN, "Incompatible shapes for a and b");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], b._data[i]), i);
    }
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::_op_clogic(const T b, bool (*fun)(T, T))
{

    if (!_check_null(this->_data, this->_shape, this->_dims))
    {
        LOG(WARN, "Null check failed on a");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], b) ? (T)1 : (T)0, i);
    }
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::_op_nlogic(const NumCpp<T> &b, bool (*fun)(T, T))
{
    if (!_check_null(this->_data, this->_shape, this->_dims))
    {
        LOG(WARN, "Null check failed on a");
        return *this;
    }
    if (!_check_null(b._data, b._shape, b._dims))
    {
        LOG(WARN, "Null check failed on b");
        return *this;
    }
    if (!_check_shape(&b))
    {
        LOG(WARN, "Incompatible shapes for a and b");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], b._data[i]) ? (T)1 : (T)0, i);
    }
    return ret;
}
