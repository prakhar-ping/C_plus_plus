#include <iostream>

double Add(double a, double b)
{
    return a + b;
}

double Subtract(double a, double b)
{
    return a - b;
}

double Multiply(double a, double b)
{
    return a * b;
}

double Divide(double a, double b)
{
    if(b == 0)
    return 0;

    return a/b;
}

int main()
{
    double num1,num2;
    char op;
    
    while(true)
    {
        std::cout<<"Inloop"<<std::endl;
        std::cout<<"Pressed Quit"<<std::endl;
        std::cin>>op;

        if(op =='q')
        {
            break;
        }

        std::cout<<"Enter number 1:"<<std::endl;
        std::cin>>num1;
        std::cout<<"Enter number 2:"<<std::endl;
        std::cin>>num2;

        switch(op)
        {
            case '+':
            {
                std::cout<<"Result = "<<Add(num1,num2)<<std::endl;
                break;
            }
            case '-':
            {
                std::cout<<"Result = "<<Subtract(num1,num2)<<std::endl;
                break;
            }
            case '*':
            {
                std::cout<<"Result = "<<Multiply(num1,num2)<<std::endl;
                break;
            } 
            case '/':
            {
                std::cout<<"Result = "<<Divide(num1,num2)<<std::endl;
                break;
            }  
            default:
            {
                std::cout<<"Invalid Operation"<<std::endl;
                break;
            }
        }
    }
    return 0;
}

