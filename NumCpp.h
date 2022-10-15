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
        LOG(INFO, __FILE__, __LINE__, "_shape is null, allocating new");
        _shape = (uint32_t *)malloc(s_dims * sizeof(uint32_t));
    }
    else
    {
        if (s_dims != _dims)
        {
            LOG(INFO, __FILE__, __LINE__, "s_dims != _dims -> reallocating _shape");
            _shape = (uint32_t *)realloc(_shape, s_dims * sizeof(uint32_t));
        }
    }

    LOG(INFO, __FILE__, __LINE__, "updating _shape");
    _shape = (uint32_t *)memcpy(_shape, s_shape, s_dims * sizeof(uint32_t));
    LOG(INFO, __FILE__, __LINE__, "updating _dims");
    _dims = s_dims;
    LOG(INFO, __FILE__, __LINE__, "updating _size");
    _size = 0;
    for (uint32_t i = 0; i < _dims; i++)
    {
        _size += _shape[i];
    }
}

template <class T>
bool NumCpp<T>::_set_data(const T *src, const uint32_t *s_shape, uint32_t s_dims)
{
    uint32_t s_size = 0;
    for (uint32_t i = 0; i < s_dims; i++)
    {
        s_size += s_shape[i];
    }
    if (_data == NULL)
    {
        LOG(INFO, __FILE__, __LINE__, "_data is null, allocating new");
        _data = (T *)calloc(s_size, sizeof(T));
        LOG(INFO, __FILE__, __LINE__, "Setting _data");
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        _upd_shape(s_shape, s_dims);
        return true;
    }
    else if (_size != s_size)
    {
        LOG(INFO, __FILE__, __LINE__, "s_size != m_size, reallocating and copying");
        _data = (T *)realloc(_data, s_size * sizeof(T));
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        _upd_shape(s_shape, s_dims);
        return true;
    }
    else if (_size == s_size)
    {
        LOG(INFO, __FILE__, __LINE__, "shapes matches -> let's copy directly");
        _data = (T *)memcpy(_data, src, s_size * sizeof(T));
        _upd_shape(s_shape, s_dims);
        return true;
    }
    LOG(IMPL, __FILE__, __LINE__, "Not implemented yet --> something missing here!");
    return false;
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
        printf(" data:\n");
        if (_dims == 1)
        {
            for (uint32_t i = 0; i < _shape[0]; ++i)
            {
                printf("R%02d: %4.3f\n", i, _data[i]);
            }
        }
        if (_dims == 2)
        {
            for (uint32_t i = 0; i < _shape[0]; ++i)
            {
                printf("R%02d:", i);
                for (uint32_t j = 0; j < _shape[1]; ++j)
                {
                    printf(" %4.3f ", _data[i * _shape[0] + j]);
                }
                printf("\n");
            }
        }

        // sLOG(IMPL, __FILE__, __LINE__, "Display data != NULL not supported yet.");
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

#endif
