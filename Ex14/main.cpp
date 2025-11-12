#include "dec.h"
#include <iostream>

int main()
{
    point p{100, 200, 300};
    std::cout << "--重置x为1000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    p = {100, 200, 300};
    std::cout << "--重置x为1000、y为2000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000, 2000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    p = {100, 200, 300};
    std::cout << "--重置x为1000、y为2000、z为3000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000, 2000, 3000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    //----------------
    point p2(100, 200, 300);
    std::cout << "--法2通过成员函数重置x为1000、y为2000、z为3000前x,y,z值: " << p2.x << ',' << p2.y << ',' << p2.z << std::endl;
    p2.reset(1000, 2000, 3000);
    std::cout << "--重置后x,y,z值: " << p2.x << ',' << p2.y << ',' << p2.z << std::endl;

    return 0;
}