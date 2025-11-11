#include "decFunction.h"
// 导入头文件中的命名空间用于区分，并且iostream也是在头文件统一导入了

void French::sayhi()
{
    std::cout << "bonjour" << std::endl;
}

void English::sayhi()
{
    std::cout << "hi" << std::endl;
}

void China::sayhi()
{
    std::cout << "你好" << std::endl;
}