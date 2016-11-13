#include <iostream>
#include <ProtobufSenderFlow.h>
#include <BdBlock.pb.h>
#include <ctime>

#include "SenderStream.hpp"

int main()
{
    BufferPool pool;
    SenderStream stream(pool, 1000);

    ProtobufSenderFlow * flow1 = stream.create_flow<ProtobufSenderFlow>("Flow1", "tcp://*:9991");

    // send data.
    BdBlock file_block;

    FILE * file = fopen("test.file", "rb");
    assert(file);

    char buffer[1024 * 1024];

    size_t sent_size;

    clock_t begin = clock();

    uint32_t i = 0;
    while (!feof(file)) {
        sent_size = fread(buffer, 1, sizeof(buffer), file);

        file_block.set_offset(i++);
        file_block.set_message(buffer, sent_size);

        flow1->send(file_block);
    }

    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Seconds: " << elapsed_secs << std::endl;

    flow1->stop();

    fclose(file);

    return 0;
}
