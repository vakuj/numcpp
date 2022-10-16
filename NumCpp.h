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
    // bool _set_row();
    // bool _set_col();
    void _insert(const T, uint32_t offset);

public:
    NumCpp();
    NumCpp(const T *, uint32_t *, uint32_t);
    NumCpp(const char *);
    ~NumCpp();

    /**
     * shapes and size of data
     */
    const uint32_t *shape(void) { return (const uint32_t *)_shape; }
    uint32_t dims(void) { return _dims; }
    uint32_t size(void) { return _size; }

    void disp(void);

    // uint32_t rows();
    // uint32_t cols();

    // void set_idx(uint32_t idx); // set the new reference index

    void set(const T *src, uint32_t *shape, uint32_t dims); // set new data
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0); // return current data

    NumCpp *zero(uint32_t *s_shape, uint32_t s_dims);

    NumCpp *operator+(const NumCpp *);
    NumCpp *operator+(const T);

    // void del(uint32_t atdim = 0, uint32_t idx = 0);                   // delete current data --> nullptr
    // void replace(const T *src, uint32_t atdim = 0, uint32_t idx = 0); // replace part of current data
    // void insert(const T *src, uint32_t atdim = 0, uint32_t idx = 0);  // inserts to data --> modifies shape

    // void get_row(T *dst, uint32_t idx = 0); // return part of data
    // void get_col(T *dst, uint32_t idx = 0); // return part of data

    // void replace_row(const T *src, uint32_t idx = 0); // replace part of data
    // void replace_col(const T *src, uint32_t idx = 0); // replace part of data

    // void del_row(uint32_t idx = 0); // remove part of data --> modifies size
    // void del_col(uint32_t idx = 0); // remove part of data --> modifies size

    // void insert_row(uint32_t idx = 0); // insert new data --> modifies size
    // void insert_col(uint32_t idx = 0); // insert new data --> modifies size
};

/** [CONSTRUCTOR / DESTRUCTOR]*/
template <class T>
NumCpp<T>::NumCpp()
{
    _data = nullptr;
    _dims = 0;
    _size = 0;
    _shape = nullptr;
}
template <class T>
NumCpp<T>::NumCpp(const T *_src, uint32_t *_s, uint32_t _d)
{
    set(_src, _s, _d);
}

template <class T>
NumCpp<T>::~NumCpp()
{
    if (_data != nullptr)
        free(_data);
    if (_shape != nullptr)
        free(_shape);
}

/** [PRIVATE] */
template <class T>
void NumCpp<T>::_upd_shape(const uint32_t *s_shape, uint32_t s_dims)
{
    if (_shape == NULL)
    {
        _shape = (uint32_t *)malloc(s_dims * sizeof(uint32_t));
    }
    else
    {
        if (s_dims != _dims)
        {
            _shape = (uint32_t *)realloc(_shape, s_dims * sizeof(uint32_t));
        }
    }

    _shape = (uint32_t *)memcpy(_shape, s_shape, s_dims * sizeof(uint32_t));
    _dims = s_dims;
    _size = 1;
    for (uint32_t i = 0; i < _dims; i++)
    {
        _size *= _shape[i];
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
    if (_data == NULL)
    {
        _data = (T *)calloc(s_size, sizeof(T));
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        NumCpp<T>::_upd_shape(s_shape, s_dims);
        return true;
    }
    else if (_size != s_size)
    {
        _data = (T *)realloc(_data, s_size * sizeof(T));
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        NumCpp<T>::_upd_shape(s_shape, s_dims);
        return true;
    }
    else if (_size == s_size)
    {
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        _upd_shape(s_shape, s_dims);
        return true;
    }
    else
        LOG(IMPL, __FILE__, __LINE__, "Not implemented yet --> Uncatched case for setting data encountered");
    return false;
}

template <class T>
void NumCpp<T>::_insert(T val, uint32_t offset)
{
    if (offset > _size)
    {
        LOG(ERROR, __FILE__, __LINE__, "Attempt at insertion outside allowed memory");
        LOG(INFO, __FILE__, __LINE__, "Insertion aborted");
        return;
    }
    _data[offset] = val;
}

/** [PUBLIC] */
template <class T>
void NumCpp<T>::disp(void)
{
    printf("\n\n==============\n");

    if (_dims > 2)
        LOG(IMPL, __FILE__, __LINE__, "Display option for dims > 2 currently not supported.");

    printf(" dims: %d\n", _dims);
    if (_shape == NULL)
    {
        printf("shape: NULL\n");
    }
    else
    {
        if (_dims == 1)
            printf("shape: %d\n", _shape[0]);
        if (_dims == 2)
            printf("shape: %d x %d\n", _shape[0], _shape[1]);
    }
    if (_data == NULL)
    {
        printf(" data: \n NULL\n");
    }
    else
    {
        printf(" data:\n    ");
        if (_dims == 1)
        {
            printf("   C00\n");
            for (uint32_t i = 0; i < _shape[0]; ++i)
            {
                printf("R%02d: %4.3f\n", i, _data[i]);
            }
        }
        if (_dims == 2)
        {
            for (uint32_t i = 0; i < _shape[1]; ++i)
                printf("   C%02d", i);
            printf("\n");
            for (uint32_t i = 0; i < _shape[0]; ++i)
            {
                printf("R%02d:", i);
                for (uint32_t j = 0; j < _shape[1]; ++j)
                {
                    printf(" %4.3f", _data[i * _shape[0] + j]);
                }
                printf("\n");
            }
        }

        // LOG(IMPL, __FILE__, __LINE__, "Display data != NULL not supported yet.");
    }
    printf("\n==============\n\n");
}

template <class T>
void NumCpp<T>::set(const T *src, uint32_t *s_shape, uint32_t s_dims)
{
    if (s_dims == 0)
    {
        LOG(WARN, __FILE__, __LINE__, "s_dims == 0 not supported. Nothing is done with _data");
        return;
    }
    bool retval = NumCpp<T>::_set_data(src, s_shape, s_dims);

    if (!retval)
        LOG(WARN, __FILE__, __LINE__, "_set_data return false...");
    else
        LOG(INFO, __FILE__, __LINE__, "_set_data return true");
}

template <class T>
NumCpp<T> *NumCpp<T>::operator+(const NumCpp<T> *other)
{

    return nullptr;
}

template <class T>
NumCpp<T> *NumCpp<T>::zero(uint32_t *s_shape, uint32_t s_dims)
{
    NumCpp<T> *ret = new NumCpp<T>();
    uint32_t s_size = 1;
    for (uint32_t i = 0; i < s_dims; ++i)
    {
        s_size *= s_shape[i];
    }

    T *src = (T *)calloc(s_size, sizeof(T));
    ret->set(src, s_shape, s_dims);
    free(src);
    return ret;
}

template <class T>
NumCpp<T> *NumCpp<T>::operator+(const T other)
{
    if (_data == NULL)
        return nullptr;
    else if (_dims == 0)
        return nullptr;
    else
    {
        if (_dims > 2)
            LOG(IMPL, __FILE__, __LINE__, "_dims > 2 not currently supported.");
        NumCpp<T> *ret = NumCpp<T>::zero(_shape, _dims);

        for (uint32_t i = 0; i < _size; ++i)
        {
            ret->_insert(_data[i] + other, i);
        }
        return ret;
    }
    return nullptr;
}
#endif
