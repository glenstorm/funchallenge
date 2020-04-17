#include <iostream>

class A
{
public:
    A()
    {
        i = 8;
    }

    virtual setI( int _i )
    {
        i = _i;
        output();
    }

    virtual output()
    {
        std::cout << "hello from A" << std::endl;
    }

protected:

    int i;
};
