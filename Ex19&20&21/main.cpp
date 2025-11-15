#include <iostream>
#include "fraction.hpp"
#include "fractionPatch.hpp"

using namespace std;
using namespace MATH;

Fraction *myFunction()
{
    Fraction fx(7, 8);
    Fraction *pfy = new Fraction(2, 3);
    return pfy;
}

int main()
{
    Fraction f1(3, 4);
    Fraction f2(1, 6);
    Fraction *pf3 = new Fraction(1, 2);

    cout << "\n---- 进入一个作用域 ----\n";
    Fraction *pf6;
    {
        Fraction f4(3, 8);
        Fraction f5(4, 6);
        pf6 = new Fraction(1, 3);
    }
    cout << "---- 离开作用域 ----\n";

    // 函数作用域
    cout << "\n---- 进入函数 ----\n";
    Fraction *pf7 = myFunction();
    cout << "---- 离开函数 ----\n";

    cout << "\n---- 手动释放内存 ----\n";
    delete pf6;
    delete pf7;
    delete pf3;

    cout << "\n---- 测试加法 ----\n";
    cout << f1.getNumerateur() << '/' << f1.getDenominateur() << " + " << f2.getNumerateur() << '/' << f2.getDenominateur() << endl;
    Fraction r = f1.somme(f2);
    r.afficher();
    cout << endl;

    // Ex20 =================================

    cout << "\n==== E20 - 测试运算符重载 ====\n";
    cout << "\n---- 测试 f1 + f2 (Fraction + Fraction) ----\n";
    Fraction f8(1, 2);
    Fraction f9(1, 3);
    cout << "f8 = " << f8 << ", f9 = " << f9 << endl;
    Fraction f10 = f8 + f9;
    cout << "f8 + f9 = " << f10 << endl;

    cout << "\n---- 测试 Fraction + int 和 int + Fraction ----\n";
    Fraction f11(2, 3);
    cout << "f11 = " << f11 << endl;
    Fraction f12 = f11 + 2;
    cout << "f11 + 2 = " << f12 << endl;
    Fraction f13 = 3 + f11;
    cout << "3 + f11 = " << f13 << endl;

    cout << "\n---- 测试 ++f 和 f++ ----\n";
    Fraction f14(3, 4);
    cout << "原始值 f14 = " << f14 << endl;

    cout << "前缀 ++f14 = " << ++f14 << endl;
    cout << "执行后 f14 = " << f14 << endl;

    Fraction f15(5, 6);
    cout << "\n原始值 f15 = " << f15 << endl;
    cout << "后缀 f15++ = " << f15++ << " (返回旧值)" << endl;
    cout << "执行后 f15 = " << f15 << endl;

    cout << "\n---- 测试 cout << f (已在上面使用) ----\n";
    cout << "链式输出测试: " << f8 << " + " << f9 << " = " << f10 << endl;

    // Ex21 =================================
    cout << "\n==== E21 - 测试异常处理 ====\n";

    cout << "\n---- 构造函数中分母为0 ----\n";
    try
    {
        Fraction f16(1, 0);
        cout << "f16 = " << f16 << endl; // 不会执行
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
        cout << "  错误的分数值: " << e.getNumerateur() << "/" << e.getDenominateur() << endl;
    }

    cout << "\n---- setFraction 中分母为0 ----\n";
    try
    {
        Fraction f17(3, 4);
        cout << "创建 f17 = " << f17 << endl;
        cout << "尝试将 f17 设置为 5/0..." << endl;
        f17.setFraction(5, 0);
        cout << "f17 = " << f17 << endl;
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
        cout << "  错误的分数值: " << e.getNumerateur() << "/" << e.getDenominateur() << endl;
    }

    cout << "\n---- 正常的分数运算 ----\n";
    try
    {
        Fraction f18(1, 2);
        Fraction f19(1, 3);
        Fraction f20 = f18 + f19;
        cout << f18 << " + " << f19 << " = " << f20 << " ✓" << endl;
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
    }

    cout << "\n---- 程序结束 ----\n";

    return 0;
}

/*
Ex19结果：

+ 构造 Fraction 对象: 0x16b5e2fb4 => 3/4
+ 构造 Fraction 对象: 0x16b5e2fac => 1/6
+ 构造 Fraction 对象: 0x120606140 => 1/2

---- 进入一个作用域 ----
+ 构造 Fraction 对象: 0x16b5e2f80 => 3/8
+ 构造 Fraction 对象: 0x16b5e2f78 => 4/6
+ 构造 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x16b5e2f78 => 2/3（p5化简后的结果）
- 析构 Fraction 对象: 0x16b5e2f80 => 3/8
---- 离开作用域 ----

---- 进入函数 ----
+ 构造 Fraction 对象: 0x16b5e2eb8 => 7/8
+ 构造 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x16b5e2eb8 => 7/8
---- 离开函数 ----

---- 手动释放内存 ----
- 析构 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x120606140 => 1/2

---- 测试加法 ----
3/4 + 1/6
+ 构造 Fraction 对象: 0x16b5e2f68 => 22/24
11/12

---- 程序结束 ----
- 析构 Fraction 对象: 0x16b5e2f68 => 11/12
- 析构 Fraction 对象: 0x16b5e2fac => 1/6
- 析构 Fraction 对象: 0x16b5e2fb4 => 3/4
*/

/*
Ex20结果：

==== E20 - 测试运算符重载 ====

---- 测试 f1 + f2 (Fraction + Fraction) ----
+ 构造 Fraction 对象: 0x16d45ef60 => 1/2
+ 构造 Fraction 对象: 0x16d45ef58 => 1/3
f8 = 1/2, f9 = 1/3
+ 构造 Fraction 对象: 0x16d45ef50 => 5/6
f8 + f9 = 5/6

---- 测试 Fraction + int 和 int + Fraction ----
+ 构造 Fraction 对象: 0x16d45ef48 => 2/3
f11 = 2/3
+ 构造 Fraction 对象: 0x16d45ef40 => 8/3
f11 + 2 = 8/3
+ 构造 Fraction 对象: 0x16d45ef38 => 11/3
3 + f11 = 11/3

---- 测试 ++f 和 f++ ----
+ 构造 Fraction 对象: 0x16d45ef30 => 3/4
原始值 f14 = 3/4
前缀 ++f14 = 7/4
执行后 f14 = 7/4
+ 构造 Fraction 对象: 0x16d45ef28 => 5/6

原始值 f15 = 5/6
后缀 f15++ = + 拷贝构造 Fraction: 0x16d45ef20 <= 0x16d45ef28
5/6 (返回旧值)
- 析构 Fraction 对象: 0x16d45ef20 => 5/6
执行后 f15 = 11/6

---- 测试 cout << f (已在上面使用) ----
链式输出测试: 1/2 + 1/3 = 5/6
*/

/*
Ex21结果

==== E21 - 测试异常处理 ====

---- 构造函数中分母为0 ----
+ 构造 Fraction 对象: 0x16f606f18 => 1/0
捕获到 FractionException 异常: 错误：分母不能为0！
  错误的分数值: 1/0

---- setFraction 中分母为0 ----
+ 构造 Fraction 对象: 0x16f606f08 => 3/4
创建 f17 = 3/4
尝试将 f17 设置为 5/0...
- 析构 Fraction 对象: 0x16f606f08 => 5/0
捕获到 FractionException 异常: 错误：分母不能为0！
  错误的分数值: 5/0

---- 正常的分数运算 ----
+ 构造 Fraction 对象: 0x16f606ef8 => 1/2
+ 构造 Fraction 对象: 0x16f606ef0 => 1/3
+ 构造 Fraction 对象: 0x16f606ee8 => 5/6
1/2 + 1/3 = 5/6 ✓
- 析构 Fraction 对象: 0x16f606ee8 => 5/6
- 析构 Fraction 对象: 0x16f606ef0 => 1/3
- 析构 Fraction 对象: 0x16f606ef8 => 1/2
*/