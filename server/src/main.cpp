#include "server.h"
#include <iostream>
#include <syncstream>

int main (int argc, char* argv[]) {
    if(argc != 2){
        std::osyncstream s_cout(std::cout);
        s_cout << "Wrong number of arguments.\n";
        return 1;
    }


    try {
        server::Server serv(atoi(argv[1]), 10, 10);
        serv.start();
    } catch(const std::exception& e) {
        std::osyncstream s_cout(std::cout);
        s_cout << e.what() << "\n";
        return 2;
    }
    return 0;
}
