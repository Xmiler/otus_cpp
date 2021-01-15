#include <sstream>
#include "lib/logger.h"
#include "lib/handler.h"


int main() {
    
    Handler handler(3);
    ConsoleLogger console_logger;
//    FileLogger file_logger("log");

    handler.subscribe(&console_logger);
//    handler.subscribe(&file_logger);

    std::stringstream input("cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n");
    handler.process(input);

}
