#ifndef NUMCPP_H
#define NUMCPP_H

#include <cstdint>

using namespace std;

template <class T>
class NumCpp
{
private:
    T *_data;

    uint32_t _ncols;
    uint32_t _nrows;
    uint32_t _dims;
    uint32_t *_shape;
    uint32_t _idx;

    char *header_info;

    bool _set_data(T **dst, const T *src, int n);
    bool _set_row();
    bool _set_col();

public:
    NumCpp();
    ~NumCpp();

    /**
     * shapes and size of data
     */
    uint32_t *shape();
    uint32_t rows();
    uint32_t cols();
    uint32_t dims();

    void set_idx(uint32_t idx); // set the new reference index

    void set(const T *src, uint32_t *shape, uint32_t dims);           // set new data
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0);           // return current data
    void del(uint32_t atdim = 0, uint32_t idx = 0);                   // delete current data --> nullptr
    void replace(const T *src, uint32_t atdim = 0, uint32_t idx = 0); // replace part of current data
    void insert(const T *src, uint32_t atdim = 0, uint32_t idx = 0);  // inserts to data --> modifies shape

    void get_row(T *dst, uint32_t idx = 0); // return part of data
    void get_col(T *dst, uint32_t idx = 0); // return part of data

    void replace_row(const T *src, uint32_t idx = 0); // replace part of data
    void replace_col(const T *src, uint32_t idx = 0); // replace part of data

    void del_row(uint32_t idx = 0); // remove part of data --> modifies size
    void del_col(uint32_t idx = 0); // remove part of data --> modifies size

    void insert_row(uint32_t idx = 0); // insert new data --> modifies size
    void insert_col(uint32_t idx = 0); // insert new data --> modifies size
};

template <class T>
NumCpp<T>::NumCpp()
{
    _data = nullptr;
}
template <class T>
NumCpp<T>::~NumCpp()
{
}

template <class T>
bool NumCpp<T>::_set_data(T **dst, const T *src, int n)
{
    if (*dst == NULL)
        *dst = (T *)calloc(n, sizeof(T));
    // if (len < n)
    //     *dst = (T *)realloc(*dst, sizeof(T) * n);
    // if (len > n)
    //     *dst = (T *)memset(*dst + len * sizeof(T), 0, (len - n) * sizeof(T));
    if (*dst == NULL)
        return false;
    *dst = (T *)memcpy(*dst, src, n * sizeof(T));

    return *dst != NULL;
}

// template <class T>
// bool NumCpp<T>::set(const T *x, int n)
// {
//     return NumCpp<T>::set_tdata(&xdata, x, n);
// }

#endif
