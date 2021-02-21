#include <sstream>
#include "lib/logger.h"
#include "lib/handler.h"


int main() {
    
    Handler handler(3);
    StandardLogger console_logger(&handler);
    FileLogger file_logger(&handler);

    std::stringstream in;
    in << std::cin.rdbuf();
    handler.process(in);
}
