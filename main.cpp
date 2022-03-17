#include "sharePtr.h"
#include <iostream>
class Test
{
public:
    Test(int a):b(a)
    {
        std::cout << "构造 " << b<< std::endl;
    }
    ~Test()
    {
        std::cout << "析构 " << b<<std::endl;
    }
    int b;
};

int main()
{
    Test * t = new Test(1);
    Test* t2 = new Test(2);
    SharePtr<Test> a(t);
    SharePtr<Test> b(a);
    std::cout << "success"<<std::endl;
}