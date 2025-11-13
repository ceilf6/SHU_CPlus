#ifndef FRACTION_PATCH_H
#define FRACTION_PATCH_H

#include "fraction.hpp"
#include <iostream>

namespace MATH
{
    Fraction operator+(const Fraction &f1, const Fraction &f2);

    Fraction operator+(const Fraction &f, int n);
    Fraction operator+(int n, const Fraction &f);

    // 前缀版本 ++f (返回引用，因为返回自身)
    Fraction &operator++(Fraction &f);
    // 后缀版本 f++ (参数 int 是哑元，用于重载)
    Fraction operator++(Fraction &f, int); // 当编译器看到 ++ 在后面的时候，实际调用的是 operator++(f, 0) 从而区分前后缀

    std::ostream &operator<<(std::ostream &os, const Fraction &f);
}

#endif
