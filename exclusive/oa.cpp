#include <iostream>

int main(){
    system("make");
    system("make -f MakefileC");
    system("make -f MakefileP");
    system("make -f MakefileI");
    system("make -f MakefilePf");
    system("make -f MakefileD");
    system("make -f MakefileCore");
    system("make -f MakefileE");
    system("make -f MakeCache");
    system("make -f MakeMotor");
    system("make -f MakeInterface");
    return 0;
}