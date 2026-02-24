#include<iostream>

class BankManager
{
    private:
        double balance;

    public:
    std::string name;
    double accNumber;

    BankManager()
    {
        balance = 0;
    }

    void AddMoney(double amt)
    {
        balance += amt;
    }

    bool WithdrawMoney(double amt)
    {
        if(balance >= amt)
        {
            balance -= amt;
            return true;
        }
        return false;
    }

    double GetBalance()
    {
        return balance;
    }
};

int main()
{
    int op;
    std::cout<<"Welcom to the bank"<<std::endl;
    BankManager manager;
    double amount;


    while(true)
    {
        std::cout<<"Choose from below menu"<<std::endl;
        std::cout<<"1 for Add money"<<std::endl;
        std::cout<<"2 for Withdraw money"<<std::endl;
        std::cout<<"3 for Check balance money"<<std::endl;
        std::cout<<"0 to QUIT"<<std::endl;

        std::cin>>op;

        if(op == 0)
        {
            std::cout<<"Thank you."<<std::endl;
            break;
        }
        
        switch(op)
        {
            case 1:
            {
                std::cout<<"Enter amount"<<std::endl;
                std::cin>>amount;
                manager.AddMoney(amount);
                break;
            }
            case 2:
            {
                std::cout<<"Enter amount"<<std::endl;
                std::cin>>amount;
                bool val = manager.WithdrawMoney(amount);

                if(val)
                {
                    std::cout<<"Amount Withdrawl Successful"<<std::endl;
                }
                else
                {
                    std::cout<<"INSUFFICIENT BALANCE!!!"<<std::endl;
                }

                break;
            }
            case 3:
            {
                std::cout<<"Current Balance : "<<manager.GetBalance()<<std::endl;
                break;
            }
            default:
            {
                std::cout<<"INVALID OPERATION"<<std::endl;
                break;
            }
        }
    }
    return 0;
}