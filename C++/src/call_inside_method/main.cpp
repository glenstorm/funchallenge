#include "A.h"
#include "B.h"

int main(int argc, char const *argv[]) {

    A a;
    a.setI(4);
    a.output();
    std::cout << "a.getFirstFuncOut() --> " << a.getFirstFuncOut() << std::endl;
    B b;
    b.setI(100);
    b.output();
    std::cout << "b.getFirstFuncOut() --> " << b.getFirstFuncOut() << std::endl;

    return 0;
}
