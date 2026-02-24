#include<iostream>

int main()
{
    int SIZE;
    double avg = 0;
    std::cout<<"Enter number of scores"<<std::endl;
    std::cin>>SIZE;
    if(SIZE>0)
    {
        int *score = new int[SIZE];
        std::cout<<"Enter scores"<<std::endl;

        for(int i =0; i < SIZE; i++)
        {
            std::cin>>score[i];
            avg += score[i];
            std::cout<<&score[i]<<"->"<<score[i]<<std::endl;
        }
        delete[] score;
        avg = avg / SIZE;
        std::cout<<"Avg = "<<avg<<std::endl;
    }
    else
    {
        std::cout<<"Arrays size can't be 0"<<std::endl;
    }
}