package com.call_inside_method;

public class MainClass
{
    public static void main( String[] args )
    {
        A a = new A();
        a.setI(4);
        a.output();
        System.out.println( "a.getFirstFuncOut() = " + String.valueOf( a.getFirstFuncOut() ) );
        B b = new B();
        b.setI(100);
        b.output();
        System.out.println( "b.getFirstFuncOut() = " + String.valueOf( b.getFirstFuncOut() ) );
    }
}
