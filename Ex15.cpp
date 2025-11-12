#include <iostream>

/*
考察内存管理
C++中 new 只需要知道类型，不需要sizeof去拿到内存该类型的大小再告知 malloc；清理的话从 C 的 free 变成了 delete（如果是数组的话还得加上[]）
*/

void essai_alloc()
{
    int *pt_int = new int;
    double *pt_double = new double[100];

    pt_double[0] = 1.0;
    pt_double[1] = 2.0;
    std::cout << "--删除前数组内容" << *pt_double << std::endl;

    delete pt_int;
    delete[] pt_double;

    // 上面 delete 悬空后下面输出的是存残留位模式按 double 解释产生的“垃圾值”
    std::cout << "--删除后数组内容" << *pt_double << std::endl;
}

int main()
{
    essai_alloc();

    return 0;
}