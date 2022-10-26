
#include "NumCpp.h"

#define NF NumCpp<float>

#define NF_DIAG(n) NumCpp<float>::diag(n)

#define NF_ZERO(m, n) NumCpp<float>::zero(m, n)
#define NF_ONES(m, n) NumCpp<float> NF::ones(m, n)
#define NF_FILL(m, n) NumCpp<float> NF::fill(m, n)

#define NF_LINSPACE(v0, v1, n) NumCpp<float>::linspace(v0, v1, n)
#define NF_ARANGE(v0, v1, d) NumCpp<float>::arange(v0, v1, d)
