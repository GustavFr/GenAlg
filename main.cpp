#include <iostream>
#include "Solve.cpp"

using namespace std;

int main()
{

    Node parent[] = {Node("x+x"),Node("x*x"),Node("x*x+x"),Node("x*2"),Node("(x+x)*2")};

    Solve solve(parent,sizeof (parent) / sizeof(parent[0]));
    return 0;
}
