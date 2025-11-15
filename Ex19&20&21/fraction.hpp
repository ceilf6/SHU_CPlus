#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include "fractionException.hpp"

namespace MATH
{
    class Fraction
    {
    private:
        int numerateur_;
        int denominateur_;
        void simplification(); // 私有化简函数

    public:
        // 重载构造函数
        Fraction(int n = 0, int d = 1); // 默认值构造
        Fraction(const Fraction &f);    // 拷贝构造

        ~Fraction();

        // 私有属性getter函数
        // getter 函数推荐写成 inline ，首先getter只需要返回属性值即可开销很小，而且大项目中类一般会在多处复用
        inline int getNumerateur() const { return numerateur_; }
        inline int getDenominateur() const { return denominateur_; }

        // setter 函数，修改私有属性
        void setFraction(int n, int d);

        // 加法
        Fraction somme(const Fraction &f) const;

        // 输出
        void afficher() const;
    };
}

#endif