#include "client.h"
#include <iostream>

int main (int argc, char* argv[])
{
    if(argc != 4) {
        std::cout << "Wrong number of arguments.\n";
        return 1;
    }

    client::Client c(argv[1], atoi(argv[2]), atoi(argv[3]));
    c.start();

    return 0;
}
