#ifndef NUMCPP_H
#define NUMCPP_H

#include <cstdint>
#include "../extra/logger.cpp"
using namespace std;

typedef struct
{
    uint32_t row;
    uint32_t col;
} loc_t;

/**
 * @brief Class for Numerical math, like NumPy for python
 *
 * @tparam T
 */
template <class T>
class NumCpp
{
private:
    T *_data;         /** memeber data */
    uint32_t _size;   /** member size */
    uint32_t _dims;   /** member dimensions */
    uint32_t *_shape; /** member shape */

    static uint32_t _get_size(const uint32_t *s_shape, uint32_t s_dims);
    void _upd_shape(const uint32_t s_size);
    void _upd_shape(const uint32_t *s_shape, uint32_t s_dims);

    void _insert(const T, uint32_t offset);
    /**
     * @brief bounds checking
     *
     * @param index index to be checked
     * @return true if inside bounds
     */
    bool _inside_bound(const uint32_t index) { return index < this->_size; }
    bool _inside_bound(const loc_t);
    bool _inside_bound(const uint32_t *, const uint32_t);

    NumCpp _op_nfun(const NumCpp &, T (*fun)(T, T));
    NumCpp _op_cfun(const T, T (*fun)(T, T));
    NumCpp _op_nlogic(const NumCpp &, bool (*fun)(T, T));
    NumCpp _op_clogic(const T, bool (*fun)(T, T));
    static NumCpp *_pre_op_nfun(NumCpp *, NumCpp *, NumCpp *, T (*fun)(T, T));
    static NumCpp *_pre_op_cfun(NumCpp *, NumCpp *, const T, T (*fun)(T, T));
    static NumCpp *_pre_op_nlogic(NumCpp *, NumCpp *, NumCpp *, bool (*fun)(T, T));
    static NumCpp *_pre_op_clogic(NumCpp *, NumCpp *, const T, bool (*fun)(T, T));

    static T _op_add(T a, T b) { return a + b; }
    static T _op_sub(T a, T b) { return a - b; }
    static T _op_mul(T a, T b) { return a * b; }
    static T _op_div(T a, T b) { return a / b; }

    static bool _op_neq(T a, T b) { return a != b; }
    static bool _op_leq(T a, T b) { return a <= b; }
    static bool _op_lt(T a, T b) { return a < b; }
    static bool _op_geq(T a, T b) { return _op_leq(b, a); }
    static bool _op_gt(T a, T b) { return _op_lt(b, a); }
    static bool _op_equ(T a, T b) { return !_op_neq(a, b); }

    bool _check_null(void) { return (this->_data != NULL && this->_shape != NULL && this->_dims != 0); }
    bool _check_null(const T *src, uint32_t *shape, uint32_t dims) { return (src != NULL && shape != NULL && dims != 0); }
    bool _check_shape(const NumCpp *other);

public:
    NumCpp();
    NumCpp(uint32_t *, uint32_t);
    NumCpp(const T *, uint32_t *, uint32_t);
    /**
     * @brief Construct a new NumCpp object by copy of data from other.
     *
     * @param other the one to copy
     */
    NumCpp(NumCpp const &other) : NumCpp(other._data, other._shape, other._dims) {}
    ~NumCpp();

    /** shapes and size of data */

    const uint32_t *shape(void);
    /**
     * @brief The dimensions of data
     *
     * @return uint32_t number of dims for shape of data
     */
    uint32_t dims(void) { return _dims; }
    /**
     * @brief The size of data
     *
     * @return uint32_t number of elements of data
     */
    uint32_t size(void) { return _size; }

    void disp(const char *msg = "no comment");

    /* Getters and setters */

    void set(const T *src, uint32_t s_size);
    void set(const T *src, uint32_t *shape, uint32_t dims);

    /** reshapers */
    NumCpp reshape(uint32_t *n_shape, uint32_t n_dims);
    NumCpp reshape(uint32_t m, uint32_t n);
    NumCpp flatten(bool to_row = false);
    NumCpp trans(void);

    /** Predefined data structures */
    /** M x N x ... */
    static NumCpp zero(uint32_t *s_shape, uint32_t s_dims);
    static NumCpp fill(uint32_t *s_shape, uint32_t s_dims, const T val);

    /**
     * @brief Create n-dimensional data specified by s_shape and s_dims filled with ones.
     *
     * @tparam T
     * @param s_shape the target shape
     * @param s_dims the target dim, i.e. number of elements in s_shape
     * @return NumCpp<T> the created n-dimensional data
     */
    static NumCpp ones(uint32_t *s_shape, uint32_t s_dims) { return NumCpp::fill(s_shape, s_dims, (T)1); }
    /** M x N */
    static NumCpp zero(uint32_t m, uint32_t n);
    static NumCpp diag(uint32_t m, uint32_t n);
    static NumCpp fill(uint32_t m, uint32_t n, const T val);
    /**
     * @brief Creates m x n data filled with ones. Failes if m == 0 && n == 0.
     *
     * @tparam T
     * @param m the m size
     * @param n the n size
     * @return NumCpp<T> the created m x n data. Empty data if failed.
     */
    static NumCpp ones(uint32_t m, uint32_t n) { return NumCpp::fill(m, n, (T)1); }
    /** N x N */
    static NumCpp zero(uint32_t n);
    static NumCpp diag(uint32_t n);
    static NumCpp fill(uint32_t n, const T val);
    /**
     * @brief Creates n x n data filled with ones. Failes if n == 0.
     *
     * @tparam T
     * @param n the n size
     * @return NumCpp<T> the created n x n data. Empty data if failed.
     */
    static NumCpp ones(uint32_t n) { return NumCpp::fill(n, (T)1); }
    /** 1 x N */
    static NumCpp arange(const T v0, const T v1, const T d, const bool end = true);
    static NumCpp linspace(const T v0, const T v1, const uint32_t n);
    /** END predefs */

    /** assertions */

    /**
     * @brief Assert that the data of the object is NULL.
     *
     * @param self the object to check
     * @return true if data is NULL
     */
    static bool assert_empty(const NumCpp self) { return self._data == NULL; }
    /**
     * @brief Asserts that the size of one object is the same as for the reference object.
     *
     * @param self the self object
     * @param ref the reference object
     * @return true if sizes are the same
     */
    static bool assert_size(const NumCpp self, const NumCpp ref) { return self._size == ref._size; }
    /**
     * @brief Asserts that the dims of one object is the same as for the reference object.
     *
     * @param self the self object
     * @param ref the reference object
     * @return true if dims are equal
     */
    static bool assert_dims(const NumCpp self, const NumCpp ref) { return self._dims == ref._dims; }
    static bool assert_shape(const NumCpp, const NumCpp);
    static bool assert_memory(const NumCpp, const NumCpp);
    static void assert_check(bool, const char *, const char *, int, const char *);
    static void xpass(bool, const char *, const char *, int, const char *);
    static void xfail(bool, const char *, const char *, int, const char *);

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

    uint32_t find(const T);
    uint32_t arg_max(void);
    uint32_t arg_min(void);

    uint32_t *find(const T, const uint32_t cnt);
    uint32_t *arg_max(const uint32_t cnt);
    uint32_t *arg_min(const uint32_t cnt);

    loc_t coord(const uint32_t index);
    loc_t *coord(uint32_t *index, const uint32_t len);

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

    /** Pre-allocated arithmetic NumCpp to NumCpp */
    static NumCpp *padd(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nfun(dst, a, b, &_op_add); }
    static NumCpp *psub(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nfun(dst, a, b, &_op_sub); }
    static NumCpp *pmul(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nfun(dst, a, b, &_op_mul); }
    static NumCpp *pdiv(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nfun(dst, a, b, &_op_div); }

    /** Pre-allocated arithmetic NumCpp to T */
    static NumCpp *padd(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_cfun(dst, a, b, &_op_add); }
    static NumCpp *psub(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_cfun(dst, a, b, &_op_sub); }
    static NumCpp *pmul(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_cfun(dst, a, b, &_op_mul); }
    static NumCpp *pdiv(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_cfun(dst, a, b, &_op_div); }

    /** comparison NumCpp to NumCpp */
    NumCpp operator==(const NumCpp &b) { return _op_nlogic(b, &_op_equ); }
    NumCpp operator!=(const NumCpp &b) { return _op_nlogic(b, &_op_neq); }
    NumCpp operator<=(const NumCpp &b) { return _op_nlogic(b, &_op_leq); }
    NumCpp operator>=(const NumCpp &b) { return _op_nlogic(b, &_op_geq); }
    NumCpp operator<(const NumCpp &b) { return _op_nlogic(b, &_op_lt); }
    NumCpp operator>(const NumCpp &b) { return _op_nlogic(b, &_op_gt); }

    /** comparison NumCpp to T */
    NumCpp operator==(const T b) { return _op_clogic(b, &_op_equ); }
    NumCpp operator!=(const T b) { return _op_clogic(b, &_op_neq); }
    NumCpp operator<=(const T b) { return _op_clogic(b, &_op_leq); }
    NumCpp operator>=(const T b) { return _op_clogic(b, &_op_geq); }
    NumCpp operator<(const T b) { return _op_clogic(b, &_op_lt); }
    NumCpp operator>(const T b) { return _op_clogic(b, &_op_gt); }

    /** Pre-allocated comparison NumCpp to NumCpp */
    static NumCpp *peq(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_equ); }
    static NumCpp *pneq(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_neq); }
    static NumCpp *pleq(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_leq); }
    static NumCpp *pgeq(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_geq); }
    static NumCpp *plt(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_lt); }
    static NumCpp *pgt(NumCpp *dst, NumCpp *a, NumCpp *b) { return _pre_op_nlogic(dst, a, b, &_op_gt); }

    /** Pre-allocated comparison NumCpp to T */
    static NumCpp *peq(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_clogic(dst, a, b, &_op_equ); }
    static NumCpp *pneq(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_clogic(dst, a, b, &_op_neq); }
    static NumCpp *pleq(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_clogic(dst, a, b, &_op_leq); }
    static NumCpp *pgeq(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_clogic(dst, a, b, &_op_geq); }
    static NumCpp *plt(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_clogic(dst, a, b, &_op_lt); }
    static NumCpp *pgt(NumCpp *dst, NumCpp *a, const T b) { return _pre_op_cqlogic(dst, a, b, &_op_gt); }

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

/**
 * @brief Construct a new NumCpp< T>:: NumCpp object with uninitialized data.
 *
 * @tparam T
 */
template <class T>
NumCpp<T>::NumCpp()
{
    this->_data = NULL;
    this->_dims = 0;
    this->_size = 0;
    this->_shape = NULL;
}
/**
 * @brief Construct a new NumCpp< T>:: NumCpp object with predefined shape and data set to zeros.
 *
 * @tparam T
 * @param s_shape shape of the data
 * @param s_dims number of dimentions of data, i.e. the number of elements in s_shape
 */
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
/**
 * @brief Construct a new NumCpp< T>:: NumCpp object with data according to content of src.
 *
 * @tparam T
 * @param src to be used to construct data
 * @param s_shape shape of the data. Each element multiplied with eachother must be <= amount of
 *                elements in src.
 * @param s_dims number of dimensions of data, i.e. number of elements in s_shape
 */
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
/**
 * @brief Destroy the NumCpp< T>:: NumCpp object and frees allocated resources.
 *
 * @tparam T
 */
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
#include "NumCpp_assert.h"

/** [PUBLIC] */

/**
 * @brief The shape of data. MUST be freed by recipient after use.
 *
 * @return const uint32_t* copy of shape of data
 */
template <class T>
const uint32_t *NumCpp<T>::shape(void)
{
    if (this->_shape == NULL)
        return NULL;
    uint32_t *ret = (uint32_t *)calloc(this->_dims, sizeof(T));
    ret = (uint32_t *)memcpy(ret, this->_shape, sizeof(T) * this->_dims);
    return ret;
}

/**
 * @brief Sets/Updates data according to src.
 *
 * @tparam T
 * @param src data to be used for setting/updating
 * @param s_size number of elements in src
 */
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
/**
 * @brief Sets/Updates data according to src.
 *
 * @tparam T
 * @param src data to be used for setting/updating
 * @param s_shape shape of the data. Each element multiplied with eachother must be <= amount of
 *                elements in src.
 * @param s_dims number of elements is s_shape
 */
template <class T>
void NumCpp<T>::set(const T *src, uint32_t *s_shape, uint32_t s_dims)
{
    if (s_dims == 0)
    {
        LOG(WARN, "s_dims == 0 not supported. Nothing is done with _data");
        return;
    }

    uint32_t s_size = _get_size(s_shape, s_dims);
    if (this->_data == NULL)
    {
        this->_data = (T *)calloc(s_size, sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
    }
    else if (this->_size != s_size)
    {
        this->_data = (T *)realloc(this->_data, s_size * sizeof(T));
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
    }
    else if (this->_size == s_size)
    {
        this->_data = (T *)memcpy(this->_data, src, s_size * sizeof(T));
        this->_upd_shape(s_shape, s_dims);
    }
    else
        LOG(IMPL, "Not implemented yet --> Uncatched case for setting data encountered");

    if (this->_data == NULL)
        LOG(ERROR, "Could not set data.");
}
/**
 * @brief Reshapes data according to n_shape and n_dims.
 *        The new shape must be compatible with the old data.
 *        dims > 2 currently not supported.
 *
 * @tparam T
 * @param n_shape the new data shape
 * @param n_dims the new data dims
 * @return NumCpp<T> the new reshaped data. Returns unmodified if failed.
 */
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
/**
 * @brief Reshapes data from current shape to m x n.
 *        Current shape must be compatible with the new.
 *        dims > 2 currently not supported.
 *
 * @tparam T
 * @param m new value for shape[0]
 * @param n new value for shape[1]
 * @return NumCpp<T> the new reshaped data. Returns unmodified if failed.
 */
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
/**
 * @brief Squashes n-dimensional data to one dimension.
 *        Default column formatted, e.g. shape[1] = 1.
 *        dim < 2 not possible
 *        dim > 2 not suppored currently.
 *
 * @tparam T
 * @param to_row if data should be row formatted (e.g. shape[0] = 1) (optional, default false)
 * @return NumCpp<T> the flattened data. Returns unmodified if failed.
 */
template <class T>
NumCpp<T> NumCpp<T>::flatten(bool to_row)
{
    if (this->_dims < 2)
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
/**
 * @brief Transposes data.
 *        dims > 2 currently not supported
 *
 * @tparam T
 * @return NumCpp<T> the transposed data. Return unmodified if failed.
 */
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

/**
 * @brief Implementation of = operator, i.e. sets this to other using
 *
 * @tparam T
 * @param other the content to be copied. No copying is done if this == &other
 * @return NumCpp<T>& dereferenced this pointer.
 */
template <class T>
NumCpp<T> &NumCpp<T>::operator=(const NumCpp<T> &other)
{
    if (this == &other)
        return *this;
    this->set(other._data, other._shape, other._dims);
    return *this;
}

/**
 * @brief Implementation of [] operator, i.e. for data member access.
 *        Get the values at from specifc row.
 *
 * @tparam T
 * @param loc the location, i.e. the row
 * @return NumCpp<T>& the copy of data from row loc. Returns empty data if failed.
 */
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
/**
 * @brief Implemetation of [] operator, i.e. for data member access.
 *        Get the value at a specific location in 2 dimensions.
 *
 * @tparam T
 * @param loc location to access data
 * @return T the value at loc. 0 if failed.
 */
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
