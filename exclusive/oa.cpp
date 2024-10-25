#include <iostream>

int main(){
    system("make");
    system("make -f MakefileC");
    system("make -f MakefileP");
    system("make -f MakefileI");
    system("make -f MakefilePf");
    system("make -f MakefileD");
    system("make -f MakefileCore");
    return 0;
}