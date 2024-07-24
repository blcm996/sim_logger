#include <iostream>
using namespace std;

#include"logger.h"

int main(){
    cout << "sim logger" << endl;
    blcm::utilty::Logger::instance()->open("./test.log");
    blcm::utilty::Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, "hello log");
    blcm::utilty::Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, "my name is %s, age is %s", "mclb", "999");
    return 0;
}