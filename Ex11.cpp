#include <iostream>

int main()
{
    /*
    const引用：引用指向的值是常量
    const 类型& ref
    类型 const& ref
    */

    // double &d1 = 36; // 非 const 的引用不能被赋临时量（这里的36会被临时隐式转换double，但是生命周期马上到头所以不能被引用）
    double d2 = 36;
    double &ref = d2;
    std::cout << "--d2: " << ref << std::endl;
    ref = 4; // 不是 const 可以直接更改
    std::cout << "--d2: " << ref << std::endl;

    const double d3 = 36;
    const double &d4 = 36; // 这里的 36 的生命周期会被延长到 d4 的作用域结束
    const double &d5 = d2;
    // d5 = 21; // 无法更改 const
    const double &d6 = d3;
    // double &ref2 = d6; // 自身得更严格，d6为const那么左边也必须得const
    int i = 4;
    // double &d7 = i; // 在需要隐式类型转换的时候赋值给引用的是中间的临时变量，比如这里就是static_cast<double>(i)，那么就和上面的非 const 引用不能被赋值临时变量一样了
    const double &d7 = i; // const 类型的可以赋值临时变量/字面量，会产生临时对象并延长其生命周期
    const double &d8 = i;
    // d8 = 3; // const了

    return 0;
}