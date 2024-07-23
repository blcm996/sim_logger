#include <iostream>
using namespace std;

#include"logger.h"

int main(){
    cout << "sim logger" << endl;
    blcm::utilty::Logger::instance()->open("./test.log");

    return 0;
}