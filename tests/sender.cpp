#include <iostream>
#include <BdFileBlock.pb.h>
#include <SenderStream.hpp>


int main()
{
    BufferPool pool;

    ProtobufSender sender("tcp://127.0.0.1:9999", pool);
    sender.set_stop_timeout(1000);

    BdFileBlock file_block;

    FILE * file = fopen("CMakeLists.txt", "rb");
    assert(file);

    char buffer[1024 * 1024];

    size_t sent_size;

    uint64_t i = 0;
    while (!feof(file)) {
        sent_size = fread(buffer, 1, sizeof(buffer), file);
	std::cout << "sent size 1: " << sent_size  << std:endl;
        file_block.set_offset(i++);
	std::cout << "offset: " << i  << std:endl;
        file_block.set_data(buffer, sent_size);

        sender.send(file_block);
    }

    sender.stop();

    return 0;
}
