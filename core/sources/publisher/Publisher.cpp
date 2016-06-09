#include <iostream>
#include <fstream>
#include "Publisher.hpp"

Publisher::Publisher(std::string ip) :
        ContextListener(ZMQ_PUB)
{
    zsocket_bind(socket, ("tcp://" + ip + ":5678").c_str());
}

void Publisher::start(std::string file_path, std::string channel)
{
    std::ifstream in(file_path, std::ios_base::binary);
    assert(in);

    std::streamoff offset = 0;
    char buffer[block_size];

    while (!zctx_interrupted) {
        advance_buffer(in, buffer, offset);

        zstr_sendm(socket, channel.c_str());
        zmq_send(socket, buffer, block_size, 0);

        wait_interval();
    }
}

void Publisher::set_block_size(size_t block_size)
{
    this->block_size = block_size;
}

void Publisher::advance_buffer(std::ifstream & in, char * buffer, std::streamoff & offset)
{
    memset(buffer, 0, block_size);

    in.seekg(offset);
    in.read(buffer, block_size);
    offset += block_size;
}
