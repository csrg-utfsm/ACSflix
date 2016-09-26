#include <iostream>
#include "Sender.h"

int main(int argc, char* argv[])
{
    unsigned char * message = (unsigned char *) "1010101010";
    Sender sender("tcp://127.0.0.1:8080");

    sender.send(message, 10);

    return 0;
}
