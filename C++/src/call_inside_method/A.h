#pragma once
#include <iostream>

class A
{
public:
    A():i(8)
    {}

    virtual void setI( int _i )
    {
        i = _i;
    }

    virtual int getFirstFuncOut() const
    {
        std::cout << "A::getFirstFuncOut()" << std::endl;
        return getSubFunction();
    }

    virtual int getSubFunction() const
    {
        std::cout << "A::getSubFunction()"  << std::endl;
        return get2SubFunction();
    }

    virtual int get2SubFunction() const
    {
        std::cout << "A::get2SubFunction()" << std::endl;
        return i * i;
    }

    virtual void output()
    {
        std::cout << "hello from A: i = " << i << std::endl;
    }

protected:

    int i;
};
