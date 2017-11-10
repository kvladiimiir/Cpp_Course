#include <cstdio>
#include <cmath>

int main()
{
    std::puts("a * x * x + b * x + c = 0");

    float a = 0;
    float b = 0;
    float c = 0;

    std::scanf("%f %f %f", &a, &b, &c);

    float x1 = (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
    float x2 = (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);

    std::printf("solution: %f %f", x1, x2);
}