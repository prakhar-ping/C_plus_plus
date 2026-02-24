#include <iostream>

int Swap(int &a,int  &b)
{
    int temp = a;
    a = b;
    b = temp;

    return 0;
}

int main()
{
    int a = 20,b =32;
    std::cout<<"Before Swap ->"<<"a = "<<a<<" "<<"b = "<<b<<std::endl;
    Swap(a,b);
    std::cout<<"After Swap ->"<<"a = "<<a<<" "<<"b = "<<b<<std::endl;
}