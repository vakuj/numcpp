#include "NumCpp.h"

template <class T>
bool NumCpp<T>::any(const T val)
{
    if (!this->_check_null())
        return false;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (this->_data[i] == val)
            return true;
    }
    return false;
}
template <class T>
bool NumCpp<T>::all(const T val)
{
    if (!this->_check_null())
        return false;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (this->_data[i] != val)
            return false;
    }
    return true;
}
template <class T>
T NumCpp<T>::sum(void)
{
    if (!this->_check_null())
        return (T)0;
    T val = 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        val += this->_data[i];
    }
    return val;
}
template <class T>
T NumCpp<T>::ave(void)
{
    T val = this->sum();
    if (this->_size == 0)
    {
        LOG(ERROR, "Cannot take average of size 0");
        return val;
    }
    val /= (T)this->_size;
    return val;
}
template <class T>
T NumCpp<T>::max(void)
{
    if (!this->_check_null())
        return (T)0;
    T val = 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (i == 0)
            val = this->_data[i];
        if (this->_data[i] > val)
            val = this->_data[i];
    }
    return val;
}
template <class T>
T NumCpp<T>::min(void)
{
    if (!this->_check_null())
        return (T)0;
    T val = 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (i == 0)
            val = this->_data[i];
        if (this->_data[i] < val)
            val = this->_data[i];
    }
    return val;
}
template <class T>
NumCpp<T> NumCpp<T>::cumsum(void)
{
    NumCpp<T> ret = NumCpp<T>(*this);
    if (!this->_check_null())
        return ret;
    T val = 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        val += this->_data[i];
        ret._data[i] = val;
    }
    return ret;
}

template <class T>
uint32_t NumCpp<T>::find(const T val)
{
    if (!this->_check_null())
        return 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (this->_data[i] == val)
            return i;
    }
    return this->_size + 1;
}
template <class T>
uint32_t NumCpp<T>::arg_max(void)
{
    return this->find(this->max());
}
template <class T>
uint32_t NumCpp<T>::arg_min(void)
{
    return this->find(this->min());
}
template <class T>
uint32_t *NumCpp<T>::find(const T val, const uint32_t cnt)
{
    if (!this->_check_null())
        return NULL;
    if (cnt == 0)
        return NULL;
    uint32_t *ret = (uint32_t *)calloc(cnt, sizeof(uint32_t));
    if (cnt == 1)
    {
        ret[0] = this->find(val);
        return ret;
    }
    uint32_t ctr = 0;
    for (uint32_t i = 0; i < this->_size; ++i)
    {
        if (this->_data[i] == val)
            ret[ctr++] = i;

        if (ctr >= cnt)
            break;
    }
    while (ctr < cnt)
    {
        ret[ctr++] = this->_size + 1;
    }
    return ret;
}
template <class T>
uint32_t *NumCpp<T>::arg_max(const uint32_t cnt)
{
    if (!this->_check_null())
        return NULL;
    if (cnt == 0)
        return NULL;

    return this->find(this->max(), cnt);
}
template <class T>
uint32_t *NumCpp<T>::arg_min(const uint32_t cnt)
{
    if (!this->_check_null())
        return NULL;
    if (cnt == 0)
        return NULL;

    return this->find(this->min(), cnt);
}

template <class T>
loc_t NumCpp<T>::coord(const uint32_t index)
{
    loc_t ret = {0, 0};
    if (!this->_check_null())
    {
        LOG(ERROR, "this is NULL");
        return ret;
    }
    if (!this->_inside_bound(index))
    {
        LOG(ERROR, "Index out-of-bounds");
        return ret;
    }
    if (this->_dims != 2)
    {
        LOG(ERROR, "Shape not compatible with 2D location");
        return ret;
    }
    ret.row = this->_row_nbr(index);
    ret.col = this->_col_nbr(index);
    return ret;
}
template <class T>
loc_t *NumCpp<T>::coord(uint32_t *index, const uint32_t len)
{
    if (len == 0)
        return NULL;
    if (!this->_check_null())
    {
        LOG(ERROR, "this is NULL");
        return NULL;
    }
    if (this->_dims != 2)
    {
        LOG(ERROR, "Shape not compatible with 2D location");
        return NULL;
    }
    loc_t *ret = (loc_t *)calloc(len, sizeof(loc_t));
    for (uint32_t i = 0; i < len; ++i)
    {
        ret[i] = this->coord(index[i]);
    }
    return ret;
}

template <class T>
NumCpp<T> NumCpp<T>::matmul(NumCpp<T> *other)
{
    NumCpp<T> ret;
    if (this->_dims != 2 || other->_dims != 2)
    {
        LOG(IMPL, "Currently only supporint 2D data");
        return ret;
    }
    if (!this->_check_null() || !other->_check_null())
    {
        LOG(ERROR, "Cannot matmul empty data");
        return ret;
    }
    if (this->_shape[1] != other->_shape[0])
    {
        LOG(ERROR, "Shapes not compatible for matmul. this->_shape[1] != other->_shape[0]");
        return ret;
    }
    ret = NumCpp<T>::zero(this->_shape[0], other->_shape[1]);
    uint32_t col = 0;
    uint32_t row = 0;
    T res = (T)0;
    for (uint32_t i = 0; i < ret._size; ++i)
    {
        res = (T)0;
        col = ret._col_nbr(i);
        row = ret._row_nbr(i);
        printf("col=%d, row=%d\n", col, row);
        for (uint32_t offset = 0; offset < this->_shape[1]; ++offset)
        {
            printf("row_elem=%f, col_elem=%f\n", this->_get_row_element(row, offset), other->_get_col_element(col, offset));
            res += (this->_get_row_element(row, offset) * other->_get_col_element(col, offset));
        }
        printf("res(%d,%d)=%f\n", col, row, res);
        ret._data[i] = res;
    }
    return ret;
}
