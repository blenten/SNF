#include "snf_tester.h"

int main (int argc, char* argv[])
{
    SNF_Tester tester;
    tester.start("1.txt", 1,10,1,10,1,1);
    return 0;
}
