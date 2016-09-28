#include <iostream>
#include "Sender.h"
#include "PBSender.h"
#include <Dummy.pb.h>
#include <unistd.h>

void mfree(void * data, void * hint)
{
	std::cout << "mfree" << std::endl;
}

int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

    //unsigned char * message = (unsigned char *) "1010101010";
    /*Sender sender("tcp://127.0.0.1:8080");

	/*
	DummyMessage dummy;
	DummyMessage entry;

	char buffer[256];

	dummy.set_id(42);
	dummy.set_message("Hello bitch!");

	dummy.SerializeToArray(buffer, 256);

	std::cout << entry.id() << std::endl;
	std::cout << entry.message() << std::endl;*/

	/*
	sleep(10);

    for (int i = 0; i < 10; i++) {
	    dummy.set_id(i);
	    dummy.set_message("AAA");
	    std::string message = dummy.SerializeAsString();
	    sender.send((unsigned char *) message.c_str(),
	                message.length()); // Ugly but test
    }




	sleep(10);
	char * message = (char *) "1010101010";
	zmq_msg_t msg;

	for (int i = 0; i < 10; ++i) {
		zmq_msg_init_data(&msg, message, strlen(message), mfree, NULL);
		sender.send(&msg);
	}*/

	BufferPool pool;
	PBSender sender("tcp://127.0.0.1:8080", pool);

	DummyMessage dummy;
	dummy.set_message("MESSAGE_CONTENT");

	sleep(10);

	for (int i = 0; i < 10; ++i) {
		dummy.set_id(i);
		sender.send(dummy);
	}

	// Theoretical solution to some problem
	sender.join();

    return 0;
}
