package com.call_inside_method;

public class B extends A
{
    protected void output()
    {
        System.out.println( "hello from B: i = " + String.valueOf( i) );
    }

    protected int getFirstFuncOut()
    {
        System.out.println( "B::getFirstFuncOut()" );
        return super.getSubFunction();
    }

    protected int getSubFunction()
    {
        System.out.println( "B::getSubFunction()" );
        return get2SubFunction();
    }

    protected int get2SubFunction()
    {
        System.out.println( "B::get2SubFunction()" );
        return i * i * i;
    }
}
