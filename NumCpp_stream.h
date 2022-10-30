#include "NumCpp.h"

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
