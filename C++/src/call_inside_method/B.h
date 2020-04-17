#pragma once
#include <iostream>
#include "A.h"

class B : public A
{
public:
    B():A()
    {}

    virtual void setI( int _i )
    {
        A::setI(i);
    }

    virtual void output()
    {
        std::cout << "hello from B: i = " << i << std::endl;
    }

    virtual int getFirstFuncOut() const
    {
        std::cout << "B::getFirstFuncOut()" << std::endl;
        return A::getSubFunction();
    }

    virtual int getSubFunction() const
    {
        std::cout << "B::getSubFunction()" << std::endl;
        return get2SubFunction();
    }

    virtual int get2SubFunction() const
    {
        std::cout << "B::get2SubFunction()" << std::endl;
        return i * i * i;
    }
};
