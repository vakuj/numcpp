#ifndef NUMCPP_H
#define NUMCPP_H

#include <cstdint>
#include "logger.cpp"
using namespace std;

typedef struct
{
    uint32_t row;
    uint32_t col;
} loc_t;

template <class T>
class NumCpp
{
private:
    T *_data;

    uint32_t _size;
    uint32_t _dims;
    uint32_t *_shape;

    static uint32_t _get_size(const uint32_t *s_shape, uint32_t s_dims);
    void _upd_shape(const uint32_t s_size);
    void _upd_shape(const uint32_t *s_shape, uint32_t s_dims);
    bool _set_data(const T *src, const uint32_t *s_shape, uint32_t s_dims);

    void _insert(const T, uint32_t offset);

    bool _inside_bound(const uint32_t);
    bool _inside_bound(const loc_t);
    bool _inside_bound(const uint32_t *, const uint32_t);

    NumCpp _op_nfun(const NumCpp &, T (*fun)(T, T));
    NumCpp _op_cfun(const T, T (*fun)(T, T));
    NumCpp _op_nlogic(const NumCpp &, bool (*fun)(T, T));
    NumCpp _op_clogic(const T, bool (*fun)(T, T));
    static T _op_add(T a, T b) { return a + b; }
    static T _op_sub(T a, T b) { return a - b; }
    static T _op_mul(T a, T b) { return a * b; }
    static T _op_div(T a, T b) { return a / b; }
    static bool _op_neq(T a, T b) { return a != b; }
    static bool _op_leq(T a, T b) { return a <= b; }
    static bool _op_les(T a, T b) { return a < b; }
    static bool _op_geq(T a, T b) { return _op_leq(b, a); }
    static bool _op_gre(T a, T b) { return _op_les(b, a); }
    static bool _op_equ(T a, T b) { return !_op_neq(a, b); }

    bool _check_null(void);
    bool _check_null(const T *src, uint32_t *shape, uint32_t dims);
    bool _check_shape(const NumCpp *b);

public:
    NumCpp();
    NumCpp(uint32_t *, uint32_t);
    NumCpp(const T *, uint32_t *, uint32_t);
    NumCpp(NumCpp const &other) : NumCpp(other._data, other._shape, other._dims) {}
    ~NumCpp();

    /** shapes and size of data */
    const uint32_t *shape(void) { return (const uint32_t *)_shape; }
    uint32_t dims(void) { return _dims; }
    uint32_t size(void) { return _size; }

    void disp(const char *msg = "no comment");

    /** Getters and setters */
    void set(const T *src, uint32_t s_size);
    void set(const T *src, uint32_t *shape, uint32_t dims); // set new data

    /** reshapers */
    NumCpp reshape(uint32_t *n_shape, uint32_t n_dims);
    NumCpp reshape(uint32_t m, uint32_t n);
    NumCpp flatten(bool to_row = false);
    NumCpp trans(void);

    /** Predefined data structures */
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
    NumCpp &operator=(const NumCpp &other);

    NumCpp &operator[](const uint32_t);
    T operator[](const loc_t);

    bool any(const T = 1);
    bool all(const T = 1);

    T sum(void);
    T ave(void);
    T max(void);
    T min(void);
    NumCpp cumsum(void);

    /** arithmetic NumCpp to NumCpp */
    NumCpp operator+(const NumCpp &b) { return _op_nfun(b, &_op_add); }
    NumCpp operator-(const NumCpp &b) { return _op_nfun(b, &_op_sub); }
    NumCpp operator*(const NumCpp &b) { return _op_nfun(b, &_op_mul); }
    NumCpp operator/(const NumCpp &b) { return _op_nfun(b, &_op_div); }

    /** arithmetic NumCpp to T */
    NumCpp operator+(const T b) { return _op_cfun(b, &_op_add); }
    NumCpp operator-(const T b) { return _op_cfun(b, &_op_sub); }
    NumCpp operator*(const T b) { return _op_cfun(b, &_op_mul); }
    NumCpp operator/(const T b) { return _op_cfun(b, &_op_div); }

    /** comparison NumCpp to NumCpp */
    NumCpp operator==(const NumCpp &b) { return _op_nlogic(b, &_op_equ); }
    NumCpp operator!=(const NumCpp &b) { return _op_nlogic(b, &_op_neq); }
    NumCpp operator<=(const NumCpp &b) { return _op_nlogic(b, &_op_leq); }
    NumCpp operator>=(const NumCpp &b) { return _op_nlogic(b, &_op_geq); }
    NumCpp operator<(const NumCpp &b) { return _op_nlogic(b, &_op_les); }
    NumCpp operator>(const NumCpp &b) { return _op_nlogic(b, &_op_gre); }

    /** comparison NumCpp to T */
    NumCpp operator==(const T b) { return _op_clogic(b, &_op_equ); }
    NumCpp operator!=(const T b) { return _op_clogic(b, &_op_neq); }
    NumCpp operator<=(const T b) { return _op_clogic(b, &_op_leq); }
    NumCpp operator>=(const T b) { return _op_clogic(b, &_op_geq); }
    NumCpp operator<(const T b) { return _op_clogic(b, &_op_les); }
    NumCpp operator>(const T b) { return _op_clogic(b, &_op_gre); }
    /** END Operators and math */

    /** TODO check functionality:
     * -> copy constructor
     * -> operator=
     */
    /** TODO implemention */
    NumCpp(const char *);
    bool save(const char *file);
    NumCpp load(const char *file);
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0);
    NumCpp sum(uint32_t dim);
    loc_t arg_max(void);
    loc_t arg_min(void);
    loc_t *arg_max(const uint32_t cnt = 1);
    loc_t *arg_min(const uint32_t cnt = 1);
    NumCpp sin(void);
    NumCpp cos(void);
    NumCpp asin(void);
    NumCpp acos(void);
    NumCpp abs(void);
    NumCpp sqrt(void);
    NumCpp det(void);
    NumCpp norm(void);
    NumCpp inv(void);
    NumCpp dot(const NumCpp a, const NumCpp b);
    NumCpp matmul(const NumCpp a, const NumCpp b);
    NumCpp &operator+=(const NumCpp &);
    NumCpp &operator-=(const NumCpp &);
    NumCpp &operator*=(const NumCpp &);
    NumCpp &operator/=(const NumCpp &);
    /** END TODO */
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
    free(_data);
    free(_shape);
}

#include "NumCpp_predefs.h"
#include "NumCpp_private.h"
#include "NumCpp_math.h"
#include "NumCpp_stream.h"

/** [PUBLIC] */
template <class T>
void NumCpp<T>::set(const T *src, uint32_t s_size)
{
    if (s_size == 0)
    {
        LOG(WARN, "s_size == 0 not supported. Nothing is done with _data");
        return;
    }

    if (this->_data == NULL)
    {
        this->_data = (T *)calloc(s_size, sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_size);
    }
    else if (this->_size != s_size)
    {
        this->_data = (T *)realloc(this->_data, s_size * sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_size);
    }
    else if (this->_size == s_size)
    {
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_size);
    }
    else
        LOG(IMPL, "Not implemented yet --> Uncatched case for setting data encountered");

    if (this->_data == NULL)
        LOG(ERROR, "Could not set data.");
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
    // dims == 2 at this point
    if ((this->_shape[0] == 1) || (this->_shape[1] == 1)) // still 1d -> just swap shape
    {
        uint32_t tmp = this->_shape[0];
        this->_shape[0] = this->_shape[1];
        this->_shape[1] = tmp;
        return *this;
    }
    if (this->_shape[0] == this->_shape[1])
    {
        for (uint32_t r = 0; r < this->_shape[0]; ++r)
        {
            for (uint32_t c = r + 1; c < this->_shape[0]; ++c)
            {
                T u = this->_data[r * this->_shape[0] + c];
                this->_data[r * this->_shape[0] + c] = this->_data[c * this->_shape[0] + r];
                this->_data[c * this->_shape[0] + r] = u;
            }
        }
        return *this;
    }
    T *t = (T *)calloc(this->_size, sizeof(T));
    for (uint32_t i = 0; i < this->_shape[0]; ++i)
    {
        for (uint32_t j = 0; j < this->_shape[1]; ++j)
        {
            t[j * this->_shape[0] + i] = this->_data[i * this->_shape[1] + j];
        }
    }
    this->_data = (T *)memcpy(this->_data, t, this->_size * sizeof(T));
    uint32_t tmp = this->_shape[0];
    this->_shape[0] = this->_shape[1];
    this->_shape[1] = tmp;
    free(t);
    return *this;
}

template <class T>
NumCpp<T> &NumCpp<T>::operator=(const NumCpp<T> &other)
{
    if (this == &other)
        return *this;
    this->set(other._data, other._shape, other._dims);
    return *this;
}

template <class T>
NumCpp<T> &NumCpp<T>::operator[](const uint32_t loc)
{
    NumCpp<T> *ret = new NumCpp<T>();
    if (!_inside_bound(loc))
    {
        LOG(ERROR, "location outside of bounds of data");
        return *ret;
    }
    T *src = (T *)calloc(this->_shape[1], sizeof(T));
    for (uint32_t i = 0; i < this->_shape[1]; ++i)
    {
        src[i] = this->_data[loc * this->_shape[0] + i];
    }
    ret->set(src, this->_shape[1]);
    free(src);
    return *ret;
}
template <class T>
T NumCpp<T>::operator[](const loc_t loc)
{
    if (!_inside_bound(loc))
    {
        /** TODO Find smart way to do univerally erronous return value */
        LOG(ERROR, "location outside of bounds of data");
        return 0;
    }
    return this->_data[loc.row * this->_shape[0] + loc.col];
}
#endif
