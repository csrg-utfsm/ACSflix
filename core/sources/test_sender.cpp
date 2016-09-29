#include <iostream>
#include "Sender.h"
#include "PBSender.h"
#include "StreamSender.h"
#include <Dummy.pb.h>
#include <unistd.h>
#include <fstream>

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
	//PBSender sender("tcp://127.0.0.1:8080", pool);
	Sender sender("tcp://127.0.0.1:8080");

	std::ifstream file;
	file.open("test_file");

	assert(file);

	StreamSender ssender(sender, file);
	ssender.attach_buffer_pool(pool);
	ssender.chunk_size(50);

	sleep(10);

	while (ssender.send_chunk());

	unsigned char * eot = (unsigned char *) "END_OF_TRANSMISSION";
	sender.send(eot, strlen((const char *) eot));

	/*DummyMessage dummy;
	dummy.set_message("MESSAGE_CONTENT");

	sleep(10);

	for (int i = 0; i < 10; ++i) {
		dummy.set_id(i);
		sender.send(dummy);
	}*/

    return 0;
}
