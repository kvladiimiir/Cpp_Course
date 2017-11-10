#include <iostream>

int main()
{
    // в цикле от 1 до 100
    for (int num = 1; num <= 100; num += 1)
    {
        // если кратно и 3 и 5
        if ((num % 3 == 0) && (num % 5 == 0))
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        // если кратно 3
        else if (num % 3 == 0)
        {
            //выводим Fizz
            std::cout << "Fizz" << std::endl;
        }
        // если кратно 5
        else if (num % 5 == 0)
        {
            //выводим Buzz
            std::cout << "Buzz" << std::endl;
        }
        // иначе выводим число
        else
        {
            //выводим число num
            std::cout << num << std::endl;
        }
    }
}