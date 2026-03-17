#include <iostream>
#include <string>

class EngineString
{
private:
    char *text;
    int length;

public:
    EngineString(const char *initialText, int len) : length(len)
    {
        text = new char[len];
        std::cout << &text << std::endl;
        for (int i = 0; i < len; i++)
        {
            text[i] = initialText[i];
        }
    }
    ~EngineString()
    {
        delete[] text;
    }

    // Copy constructor
    EngineString(const EngineString &other)
    {
        length = other.length;
        text = new char[length];
        for (int i = 0; i < length; i++)
        {
            text[i] = other.text[i];
        }
        std::cout << "Deep Copied  performed" << std::endl;
    }

    // Copy assignment operator
    EngineString &operator=(const EngineString &other)
    {
        if (this == &other)
        {
            return *this;
        }
        length = other.length;
        delete[] text;

        text = new char[length];
        for (int i = 0; i < length; i++)
        {
            text[i] = other.text[i];
        }
        std::cout << "Copied Assignment!!" << std::endl;
        return *this;
    }

    EngineString(EngineString &&other)
    {
        length = other.length;
        text = other.text;

        other.length = 0;
        other.text = nullptr;
    }

    EngineString &operator=(EngineString &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] text;
        length = other.length;
        text = other.text;

        other.length = 0;
        other.text = nullptr;
        return *this;
    }
};

int main()
{
    EngineString engin("P", 2);
    EngineString e2 = engin;
    EngineString s1("First", 5);
    EngineString s2("Second", 6);
    s1 = s2;
    return 0;
}