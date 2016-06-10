#include <iostream>
#include <fstream>
#include "Publisher.hpp"

Publisher::Publisher(std::string ip) :
        DataEndPoint(ZMQ_PUB)
{
    zsocket_bind(socket, ("tcp://" + ip + ":5678").c_str());
}

void Publisher::start(std::string file_path, std::string channel)
{
    FILE * file = fopen(file_path.c_str(), "rb");
    assert(file);

    long size = get_file_block_count(file_path);

    long block_cursor = 0;
    byte buffer[block_size];

    char num_buffer[50];

    zclock_sleep(1000);

    while (!zctx_interrupted) {
        sprintf(num_buffer, "%lu", block_cursor);

        zstr_sendm(socket, channel.c_str());
        zstr_sendm(socket, num_buffer);
        zmq_send(socket, buffer, block_size, 0);

        if (block_cursor % 100 == 0) {
            std::cout << block_cursor * 100.0f / size << "%" << std::endl;
        }

        wait_interval();

        if (feof(file)) {
            return;
        }

        advance_buffer(file, buffer, block_cursor);
    }
}

void Publisher::set_block_size(size_t block_size)
{
    this->block_size = block_size;
}

void Publisher::advance_buffer(FILE * file, void * buffer, long & block_cursor)
{
    memset(buffer, 0, block_size);
    fread(buffer, 1, block_size, file);
    block_cursor++;
}

long Publisher::get_file_block_count(std::string file_path)
{
    struct stat st;
    stat(file_path.c_str(), &st);
    return st.st_size / block_size;
}
