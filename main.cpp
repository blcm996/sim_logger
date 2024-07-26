#include <iostream>
using namespace std;
#include"logger.h"
using namespace blcm::utility;

int main(){
    Logger::instance()->open("./test.log");
    Logger::instance()->max(10);

    debug("hello log");
    debug("name is %s. age is %d", "jack", 18);
    info("info message");
    warn("waring");
    error("ERROR!");
    
    return 0;
}
