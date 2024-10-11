#include <iostream>

int main(){
    system("make");
    system("make -f MakefileC");
    system("make -f MakefileP");
    system("make -f MakefileI");
    return 0;
}