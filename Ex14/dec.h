#ifndef DEC_H
#define DEC_H

// #include <optional>

struct point
{
    int x;
    int y;
    int z;

    // 默认构造函数（不写也默认）
    point() : x(0), y(0), z(0) {}

    // 可选参数构造函数
    point(int xVal, int yVal = 0, int zVal = 0)
        : x(xVal), y(yVal), z(zVal) {}

    // 法2: 通过成员函数：重置
    void reset(int a = 0, int b = 0, int c = 0)
    {
        x = a;
        y = b;
        z = c;
    }
};

// 法1: 这道题想要实现多参数的初始化，第一想法就是通过可选参数，像JS中可以直接通过 ?: 来实现，
// C++的话可以通过设置默认参数来降级实现，或者利用 std::optional 来实现（注意需要 C++17 up）
// void init(point *p, std::optional<int> x = std::nullopt, std::optional<int> y = std::nullopt, std::optional<int> z = std::nullopt);
void init(point *p, int x = 0, int y = 0, int z = 0) noexcept;

#endif