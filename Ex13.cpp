#include <iostream>
/*
题面：编写一个名为raz的函数，用于将传入参数中的此类结构体中两个字段重置为零。
使用地址参数执行一次，使用引用参数执行一次。在这两种情况下，都需要编写一个简单的函数测试程序。该程序在调用此函数后会显示此类结构体的值
*/

struct essai
{
    int n;
    float x;
};

// 利用重载性质（虽然在其他语言中最好是通过详细名字区分函数，但是C++可以利用重载自动分流优化性能）
/**
 * 此处是函数说明，用于仓库代码的维护，本课程不需要，但是工程化最好多注明方便他人进一步贡献
 * @brief Reset fields of essai to zero (pass by address)
 * @param e Pointer to essai struct
 */
void raz(struct essai *e) noexcept // noexcept 是为了防止处理 const 的时候编译抛错误
{
    // 拿到结构体指针需要先解引用再拿元素值 (*p).n ，那么有一个等价语法糖就是 p->n （如果是引用的话就像下面一样直接 . 去拿即可）
    e->n = 0;
    e->x = 0.0f; // 给 float 加 f 否则数字默认是 double 会有一次隐式转换
}
/**
 * @brief Reset fields of essai to zero (pass by reference)
 * @param e Reference to essai struct
 */
void raz(struct essai &e) noexcept
{
    e.n = 0;
    e.x = 0.0f;
}

int main()
{
    essai E{100, -100.0f};
    std::cout << "--通过指针重置前对象中的n,x值:" << E.n << ',' << E.x << std::endl;
    raz(&E);
    std::cout << "--通过指针重置后对象中的n,x值:" << E.n << ',' << E.x << std::endl;

    // ----------
    E = {-100, 100.0f}; // 等价于下面两句
    // E.n = -100;
    // E.x = 100.0f;
    std::cout << "--通过引用重置前对象中的n,x值:" << E.n << ',' << E.x << std::endl;
    raz(E);
    std::cout << "--通过引用重置后对象中的n,x值:" << E.n << ',' << E.x << std::endl;

    return 0;
}