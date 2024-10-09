#include "C:\DataStructures\Lab02\Lab02\include\arraylist.h"

namespace testing
{
    /// <summary>
    /// regular constructor
    /// </summary>
    Foo::Foo() : val(0), str("") {}

    /// <summary>
    /// constructor that takes values and strings
    /// </summary>
    Foo::Foo(int v, std::string n) : val(v), str(n) {}

    int Foo::getVal() const 
    {
        return val;
    }

    void Foo::setVal(int v) 
    {
        val = v;
    }

    const std::string& Foo::getStr() const 
    {
        return str;
    }

    void Foo::setStr(const std::string& n) 
    {
        str = n;
    }
}