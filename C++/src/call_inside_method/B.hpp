#include <iostream>

class B : public A
{
public:
    B():A()
    {}

    virtual setI( int _i )
    {
        A::setI();
    }

    virtual output()
    {
        std::cout << "hello from B" << " i = " << i << std::endl;
    }

private:

    int i;
};
