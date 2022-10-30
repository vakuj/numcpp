# NumCpp

*This is **not** a replacement for **NumPy** or any other proper library. If you need some kind of guarantee that stuff actually performs as expected, you should look elsewhere.* :)

## What is it? 

Ever heard of or used NumPy? This is heavily inspired by just that. But written in and for **C++**. 

## But why?

Ehm... for funsies..? I wanted to learn some C++ and this idea came to mind.  

## But is it novel?

No, likely not. Probably reinventing the wheel here, but part of the fun is to try figuring out how it works in the background. No spoilers, please :) 


## Ok, what can it do?

Mainly basic stuff at the moment, for example, array creation and modification, element-wise math, element-wise logic, etc. 

To demonstrate: 

```c++
    NumCpp<float> a = NumCpp<float>::ones(3); // 3x3 array with ones
    NumCpp<float> b = NumCpp<float>::linspace(0.f, 9.f, 9).reshape(3, 3); // reshape 9 elements to 3x3 array
    a.disp("a");  // display the arrays
    b.disp("b");  // display the arrays
    NumCpp<float> c, d; // initialize empty 
    c = a + b; // Ok
    c.disp("c = a + b");
    c = a - b; // Ok
    c.disp("c = a - b");
    c = a * b; // Ok
    c.disp("c = a * b");
    c = a / b; // Ok
    c.disp("c = a / b");

    d = a + 3.f; // Ok
    d = a - 3.f; // Ok
    d = a * 3.f; // Ok
    d = a / 3.f; // Ok
    // d = 3.f + a; // not supported

    NumCpp<float> e = NumCpp<float>(b).trans();   // Copy b and transpose
    NumCpp<float> f = NumCpp<float>(e).flatten(); // Copy e and flatten to 1d
    e.disp("e");
    f.disp("f");

    NumCpp<float> g = a / b < .3f; // create a mask where elements of a/b are smaller than 0.3
    g.disp("g");
    NumCpp<float> h = b * g; // apply mask g to a
    h.disp("h");

```
See file [example_output.txt](example_output.txt) for output from `disp`.

`<float>` can be exchanged to any numerical type, that is, `<int32_t>`, `<uint8_t>` etc. No testing has been made for other than `<float>`.

Already tired of typing `NumCpp<float>`? Try adding `#include NumCpp_helpers.h`. Now every `NumCpp<float>` can be replaced `NF`. [NumCpp_helpers.h](NumCpp_helpers.h) includes other macros as well. The above example can be rewritten as

```c++
#include "NumCpp_defs.h"
...
    NF a = NF_ONES(3,3); 
    NF b = NF_LINSPACE(0.f, 9.f, 9).reshape(3, 3);
    ...
    NF c, d; 
    ...
    ... 
    ...  
    NF e = NF(b).trans();
    NF f = NF(e).flatten(); 
    ...
    NF g = a / b < .3f; 
    ...
    NF h = b * g; 
    ...
```

Don't like it or something missing? Create your own macros easily!

## Is it stable? 

Define "stable"? No rigorous testing has been made, but it *feels* correct :) 

## Release schedule

Nothing scheduled. Most progress probably on weekends if there is time to spare...

## TODOs  

1. Documentation
    1. Simple description of **all** functions.
1. Some kind of testing module, for example pass/fail assertion testing comparing recieved output with expected output. 
    1. Could perhaps be done with the logic operators?
    1. Well formed assertion failed messages are desired.
    1. Both expected pass and expected fail testing should be performed
1. Suggested expansions:
```c++
    NumCpp(const char *);
    bool save(const char *file);
    NumCpp load(const char *file);
    void get(T *dst, uint32_t atdim = 0, uint32_t idx = 0);
    T sum(void);
    NumCpp sum(uint32_t dim);
    NumCpp cumsum(void);
    T max(void);
    T ave(void);
    T min(void);
    loc_t arg_max(void);
    loc_t arg_ave(void);
    loc_t arg_min(void);
    loc_t *arg_max(const uint32_t cnt = 1);
    loc_t *arg_ave(const uint32_t cnt = 1);
    loc_t *arg_min(const uint32_t cnt = 1);
    NumCpp sin(void);
    NumCpp cos(void);
    NumCpp asin(void);
    NumCpp acos(void);
    NumCpp abs(void);
    NumCpp sqrt(void);
    NumCpp dot(const NumCpp a, const NumCpp b);
    NumCpp matmul(const NumCpp a, const NumCpp b);
    NumCpp det(const NumCpp a, const NumCpp b);
    NumCpp norm(const NumCpp a, const NumCpp b);
    NumCpp inv(const NumCpp a, const NumCpp b);
    NumCpp &operator+=(const NumCpp &);
    NumCpp &operator-=(const NumCpp &);
    NumCpp &operator*=(const NumCpp &);
    NumCpp &operator/=(const NumCpp &);
 ```