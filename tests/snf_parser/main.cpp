#include "../../classes/snf_parser/expandedformparser.h"
#include "../../classes/snf_minimizer/snf_minimizer.h"
#include <assert.h>
#include <iostream>

//unit test for parser. cause i really fucked with these bugs
int main()
{
    SNF_Minimizer m;
    m.parse("(x1+x2+x3)*(x1+x2+x3)");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="(x1+x2+x3)");

    m.parse("(((x1+x2))(!x1+x2))");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="(x2)");

    m.parse("(x1+x2+x3)(x1+x2+!x3)");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="(x1+x2)");

    m.parse("((((x1))))");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="(x1)");

    m.parse("x1+!x1");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="1");

    m.parse("((x1+x2)(x1+!x2)(!x1+x2)(!x1+!x2))");
    m.match();
    m.delUnness();
    assert(m.res_toString()=="(1)");

    std::cerr<<"All test succeed\n";
    return 0;
}
