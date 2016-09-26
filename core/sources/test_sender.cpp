#include <iostream>
#include "Sender.h"
#include <Dummy.pb.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

    //unsigned char * message = (unsigned char *) "1010101010";
    Sender sender("tcp://127.0.0.1:8080");

	DummyMessage dummy;

	sleep(10);

    for (int i = 0; i < 10; i++) {
	    dummy.set_id(i);
	    dummy.set_message("AAA");
	    std::string message = dummy.SerializeAsString();
	    sender.send((unsigned char *) message.c_str(),
	                message.length()); // Ugly but test
    }

    return 0;
}
