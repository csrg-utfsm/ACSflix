#include <iostream>
#include <ProtobufSenderFlow.h>
#include <BdBlock.pb.h>

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

    uint32_t i = 0;
    while (!feof(file)) {
        sent_size = fread(buffer, 1, sizeof(buffer), file);

        file_block.set_offset(i++);
        file_block.set_message(buffer, sent_size);

        flow1->send(file_block);
    }

    flow1->stop();

    fclose(file);

    return 0;
}
