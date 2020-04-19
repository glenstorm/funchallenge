package com.call_inside_method;

public class A
{
    protected void setI( int _i )
    {
        i = _i;
    }

    protected int getFirstFuncOut()
    {
        System.out.println( "A::getFirstFuncOut()" );
        return getSubFunction();
    }

    protected int getSubFunction()
    {
        System.out.println( "A::getSubFunction()" );
        return get2SubFunction();
    }

    protected int get2SubFunction()
    {
        System.out.println( "A::get2SubFunction()" );
        return i * i;
    }

    protected void output()
    {
        System.out.println( "hello from A: i = " + String.valueOf( i ) );
    }

    protected int i;
}
