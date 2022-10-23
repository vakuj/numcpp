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

    static uint32_t _get_size(const uint32_t *s_shape, uint32_t s_dims);
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

    /** shapes and size of data */
    const uint32_t *shape(void) { return (const uint32_t *)_shape; }
    uint32_t dims(void) { return _dims; }
    uint32_t size(void) { return _size; }

    void disp(const char *msg = "no comment");

    /** Getters and setters */
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0); // return current data
    void set(const T *src, uint32_t *shape, uint32_t dims); // set new data

    /** reshapers */
    NumCpp reshape(uint32_t *n_shape, uint32_t n_dims);
    NumCpp reshape(uint32_t m, uint32_t n);
    NumCpp flatten(bool to_row = false);
    NumCpp trans(void);

    /** Predefined data structures
     * See NumCpp_predefs.h
     */
    /** M x N x ... */
    static NumCpp zero(uint32_t *s_shape, uint32_t s_dims);
    static NumCpp diag(uint32_t *s_shape, uint32_t s_dims);
    static NumCpp fill(uint32_t *s_shape, uint32_t s_dims, const T val);
    static NumCpp ones(uint32_t *s_shape, uint32_t s_dims) { return NumCpp::fill(s_shape, s_dims, (T)1); }
    /** M x N */
    static NumCpp zero(uint32_t m, uint32_t n);
    static NumCpp diag(uint32_t m, uint32_t n);
    static NumCpp fill(uint32_t m, uint32_t n, const T val);
    static NumCpp ones(uint32_t m, uint32_t n) { return NumCpp::fill(m, n, (T)1); }
    /** N x N */
    static NumCpp zero(uint32_t n);
    static NumCpp diag(uint32_t n);
    static NumCpp fill(uint32_t n, const T val);
    static NumCpp ones(uint32_t n) { return NumCpp::fill(n, (T)1); }
    /** 1 x N */
    static NumCpp arange(const T v0, const T v1, const T d, const bool end = true);
    static NumCpp linspace(const T v0, const T v1, const uint32_t n);
    /** END predefs */

    /** Operators and math */
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

#include "NumCpp_predefs.h"
#include "NumCpp_private.h"

template <class T>
NumCpp<T>::~NumCpp()
{
}
/** [PUBLIC] */
template <class T>
void NumCpp<T>::disp(const char *msg)
{
    printf("\n\n===============\n  msg: %s\n", msg);

    if (this->_dims > 2)
    {
        LOG(IMPL, "Display option for dims > 2 currently not supported.");
        return;
    }

    printf(" dims: %d\n", this->_dims);
    if (this->_shape == NULL)
    {
        printf("shape: NULL\n");
        return;
    }
    else
    {
        if (this->_dims == 1)
        {
            printf("shape: %d\n", this->_shape[0]);
            if (this->_shape[0] > 100)
            {
                LOG(ERROR, "Seg fault capture");
                LOG(INFO, "shape[0] > 100 --> returning early");
                return;
            }
        }
        if (this->_dims == 2)
        {

            printf("shape: %d x %d\n", this->_shape[0], this->_shape[1]);
            if (this->_shape[0] > 100 || this->_shape[1] > 100)
            {
                LOG(ERROR, "Seg fault capture");
                LOG(INFO, "shape[0/1] > 100 --> returning early");
                return;
            }
        }
    }
    if (this->_data == NULL)
    {
        printf(" data: \n NULL\n");
        return;
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
            uint32_t rctr = 0;
            for (uint32_t i = 0; i < this->_size; ++i)
            {
                if (((i % this->_shape[1]) == 0))
                {
                    printf("\nR%02d:", rctr++);
                }
                printf(" %4.3f", this->_data[i]);
            }
        }
        printf("\n");
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
        LOG(ERROR, "Could not set data.");
}

template <class T>
NumCpp<T> NumCpp<T>::reshape(uint32_t *n_shape, uint32_t n_dims)
{
    if (n_shape == NULL)
    {
        LOG(ERROR, "Cannot reshape to empty data structure (n_shape = NULL)");
        return *this;
    }
    if (n_dims == 0)
    {
        LOG(ERROR, "Cannot reshape to empty data structure (n_dims = 0)");
        return *this;
    }
    if (n_dims > 2)
    {
        LOG(ERROR, "Cannot reshape to higher dimensions (n_dims > 2) ");
        LOG(IMPL, "Feature not implemented yet");
        return *this;
    }
    return this->reshape(n_shape[0], n_shape[1]);
}
template <class T>
NumCpp<T> NumCpp<T>::reshape(uint32_t m, uint32_t n)
{
    if (m == 0 || n == 0)
    {
        LOG(ERROR, "Cannot reshape to empty data structure (m = 0 and/or n = 0)");
        return *this;
    }
    if (this->_dims == 0)
    {
        LOG(ERROR, "Cannot reshape empty data structure (dims = 0)");
        return *this;
    }
    if (this->_dims > 2)
    {
        LOG(ERROR, "Cannot reshape higher dimensions (dims > 2) ");
        LOG(IMPL, "Feature not implemented yet");
        return *this;
    }
    if (m * n != this->_size)
    {
        LOG(ERROR, "Cannot reshape due to size mismatch (m x n != size)");
        return *this;
    }
    if (m == 1)
        return this->flatten(true);
    if (n == 1)
        return this->flatten(false);
    if (this->_dims == 1)
    {
        this->_dims = 2;
        this->_shape = (uint32_t *)realloc(this->_shape, this->_dims * sizeof(uint32_t));
        this->_shape[0] = m;
        this->_shape[1] = n;
        return *this;
    }
    // shape must be 2 here
    this->_shape[0] = m;
    this->_shape[1] = n;

    return *this;
}
template <class T>
NumCpp<T> NumCpp<T>::flatten(bool to_row)
{
    if (this->_dims <= 1)
    {
        LOG(ERROR, "Cannot flatten a flattened (or zero) data structure (dims <= 1)");
        return *this;
    }
    if (this->_dims > 2)
    {
        LOG(ERROR, "Cannot flatten higher dimensions (dims > 2) ");
        LOG(IMPL, "Feature not implemented yet");
        return *this;
    }
    // shape must be 2 here
    if (to_row)
    {
        this->_shape[0] = 1;
        this->_shape[1] = this->_size;
    }
    else
    {
        this->_shape[0] = this->_size;
        this->_shape[1] = 1;
    }
    return *this;
}
template <class T>
NumCpp<T> NumCpp<T>::trans(void)
{
    if (this->_data == NULL)
    {
        LOG(ERROR, "Cannot transpose empty data (data = NULL)");
        return *this;
    }
    if (this->_dims > 2)
    {
        LOG(ERROR, "Cannot transpose higher dimensions (dims > 2)");
        LOG(IMPL, "Feature not implemented yet");
        return *this;
    }
    if (this->_dims == 1)
    {
        // from m x 1 to 1 x m -> only needs shape change.
        this->_dims = 2;
        this->_shape = (uint32_t *)realloc(this->_shape, sizeof(uint32_t) * this->_dims);
        this->_shape[0] = 1;
        this->_shape[1] = this->_size;
        return *this;
    }

    LOG(IMPL, "Not implemented yet");

    return *this;
}
/** Operators */
template <class T>
NumCpp<T> &NumCpp<T>::operator+=(const NumCpp<T> &b)
{
    return this;
}

#endif
