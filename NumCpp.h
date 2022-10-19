#ifndef NUMCPP_H
#define NUMCPP_H

#include <cstdint>
#include "logger.cpp"
using namespace std;

template <class T>
class NumCpp
{
private:
    T *_data;

    uint32_t _size;
    uint32_t _dims;
    uint32_t *_shape;

    void _upd_shape(const uint32_t *s_shape, uint32_t s_dims);
    bool _set_data(const T *src, const uint32_t *s_shape, uint32_t s_dims);

    void _insert(const T, uint32_t offset);

    NumCpp _op_nfun(const NumCpp &, T (*fun)(T, T));
    NumCpp _op_cfun(const T, T (*fun)(T, T));
    static T _op_add(T a, T b) { return a + b; }
    static T _op_sub(T a, T b) { return a - b; }
    static T _op_mul(T a, T b) { return a * b; }
    static T _op_div(T a, T b) { return a / b; }

    bool _check_null(const T *src, uint32_t *shape, uint32_t dims);
    bool _check_shape(const NumCpp *b);

public:
    NumCpp();
    NumCpp(uint32_t *, uint32_t);
    NumCpp(const T *, uint32_t *, uint32_t);
    NumCpp(const char *);
    ~NumCpp();

    /**
     * shapes and size of data
     */
    const uint32_t *shape(void) { return (const uint32_t *)_shape; }
    uint32_t dims(void) { return _dims; }
    uint32_t size(void) { return _size; }

    void disp(const char *msg = "no comment");

    void set(const T *src, uint32_t *shape, uint32_t dims); // set new data
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0); // return current data

    static NumCpp zero(uint32_t *s_shape, uint32_t s_dims);

    NumCpp &operator+=(const NumCpp &);
    NumCpp &operator-=(const NumCpp &);
    NumCpp &operator*=(const NumCpp &);
    NumCpp &operator/=(const NumCpp &);

    NumCpp operator+(const NumCpp &b) { return _op_nfun(b, &_op_add); }
    NumCpp operator-(const NumCpp &b) { return _op_nfun(b, &_op_sub); }
    NumCpp operator*(const NumCpp &b) { return _op_nfun(b, &_op_mul); }
    NumCpp operator/(const NumCpp &b) { return _op_nfun(b, &_op_div); }

    NumCpp operator+(const T b) { return _op_cfun(b, &_op_add); }
    NumCpp operator-(const T b) { return _op_cfun(b, &_op_sub); }
    NumCpp operator*(const T b) { return _op_cfun(b, &_op_mul); }
    NumCpp operator/(const T b) { return _op_cfun(b, &_op_div); }
};

/** [CONSTRUCTOR / DESTRUCTOR]*/
template <class T>
NumCpp<T>::NumCpp()
{
    this->_data = nullptr;
    this->_dims = 0;
    this->_size = 0;
    this->_shape = nullptr;
}
template <class T>
NumCpp<T>::NumCpp(uint32_t *s_shape, uint32_t s_dims)
{
    this->_shape = (uint32_t *)calloc(s_dims, sizeof(uint32_t));
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
        this->_shape[i] = s_shape[i];
    }
    this->_data = (T *)calloc(s_size, sizeof(T));
    this->_dims = s_dims;
    this->_size = s_size;
}
template <class T>
NumCpp<T>::NumCpp(const T *src, uint32_t *s_shape, uint32_t s_dims)
{
    this->_shape = (uint32_t *)calloc(s_dims, sizeof(uint32_t));
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
        this->_shape[i] = s_shape[i];
    }
    this->_data = (T *)calloc(s_size, sizeof(T));
    this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
    this->_dims = s_dims;
    this->_size = s_size;
}

template <class T>
NumCpp<T>::~NumCpp()
{
}

/** [PRIVATE] */
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
bool NumCpp<T>::_set_data(const T *src, const uint32_t *s_shape, uint32_t s_dims)
{
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; i++)
    {
        s_size *= s_shape[i];
    }
    if (this->_data == NULL)
    {
        this->_data = (T *)calloc(s_size, sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        NumCpp<T>::_upd_shape(s_shape, s_dims);
        return true;
    }
    else if (this->_size != s_size)
    {
        this->_data = (T *)realloc(this->_data, s_size * sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
        return true;
    }
    else if (this->_size == s_size)
    {
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
        return true;
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

/** [PUBLIC] */
template <class T>
void NumCpp<T>::disp(const char *msg)
{
    printf("\n\n===============\n  msg: %s\n", msg);

    if (this->_dims > 2)
        LOG(IMPL, "Display option for dims > 2 currently not supported.");

    printf(" dims: %d\n", this->_dims);
    if (this->_shape == NULL)
    {
        printf("shape: NULL\n");
    }
    else
    {
        if (this->_dims == 1)
        {
            if (this->_shape[0] > 100)
            {
                LOG(ERROR, "Seg fault capture");
                LOG(INFO, "shape[0] > 100 --> returning early");
                return;
            }
            printf("shape: %d\n", this->_shape[0]);
        }
        if (this->_dims == 2)
        {

            if (this->_shape[0] > 100 || this->_shape[1] > 100)
            {
                LOG(ERROR, "Seg fault capture");
                LOG(INFO, "shape[0/1] > 100 --> returning early");
                return;
            }
            printf("shape: %d x %d\n", this->_shape[0], this->_shape[1]);
        }
    }
    if (this->_data == NULL)
    {
        printf(" data: \n NULL\n");
    }
    else
    {
        printf(" data:\n    ");
        if (this->_dims == 1)
        {
            printf("   C00\n");
            for (uint32_t i = 0; i < this->_shape[0]; ++i)
            {
                printf("R%02d: %4.3f\n", i, this->_data[i]);
            }
        }
        if (this->_dims == 2)
        {
            for (uint32_t i = 0; i < this->_shape[1]; ++i)
                printf("   C%02d", i);
            printf("\n");
            for (uint32_t i = 0; i < this->_shape[0]; ++i)
            {
                printf("R%02d:", i);
                for (uint32_t j = 0; j < this->_shape[1]; ++j)
                {
                    printf(" %4.3f", this->_data[i * this->_shape[0] + j]);
                }
                printf("\n");
            }
        }
    }
}

template <class T>
void NumCpp<T>::set(const T *src, uint32_t *s_shape, uint32_t s_dims)
{
    if (s_dims == 0)
    {
        LOG(WARN, "s_dims == 0 not supported. Nothing is done with _data");
        return;
    }
    bool retval = this->_set_data(src, s_shape, s_dims);

    if (!retval)
        LOG(WARN, "_set_data return false...");
    else
        LOG(INFO, "_set_data return true");
}

template <class T>
NumCpp<T> NumCpp<T>::zero(uint32_t *s_shape, uint32_t s_dims)
{
    NumCpp<T> ret;
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
    }

    T *src = (T *)calloc(s_size, sizeof(T));
    ret.set(src, s_shape, s_dims);
    free(src);
    return ret;
}
template <class T>
NumCpp<T> &NumCpp<T>::operator+=(const NumCpp<T> &b)
{
    return this;
}

template <class T>
NumCpp<T> NumCpp<T>::_op_cfun(const T b, T (*fun)(T, T))
{

    if (!_check_null(this->_data, this->_shape, this->_dims))
        return *this;
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
        LOG(INFO, "returned early here");
        return *this;
    }
    if (!_check_null(b._data, b._shape, b._dims))
    {
        LOG(INFO, "returned early here");
        return *this;
    }
    if (!_check_shape(&b))
    {
        LOG(INFO, "returned early here");
        return *this;
    }
    NumCpp<T> ret(this->_shape, this->_dims);
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        ret._insert(fun(this->_data[i], b._data[i]), i);
    }
    return ret;
}
#endif
