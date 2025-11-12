#include "dec.h"

void init(point *p, int x, int y, int z) noexcept // 注意在声明的时候写了默认参数后在定义不需要再写一遍
{
    p->x = x;
    p->y = y;
    p->z = z;
}