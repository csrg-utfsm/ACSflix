#include <iostream>
#include <fstream>
#include "Publisher.hpp"

Publisher::Publisher() :
        DataEndPoint(ZMQ_PUB)
{
    zsocket_bind(socket, "tcp://*:5678");
}

void Publisher::start(std::string file_path, std::string channel)
{
    FILE * file = fopen(file_path.c_str(), "rb");
    assert(file);

    long file_size = get_file_size(file_path);
    long block_count = (long) ceil((float) file_size / block_size);

    long block_cursor = 0;
    byte buffer[block_size];

    std::cout << "Blocks: " << block_count << std::endl;

    zclock_sleep(1000);

    struct timeval tv;
    suseconds_t last_time;
    suseconds_t time_difference;
    suseconds_t current_time;

    gettimeofday(&tv, nullptr);
    last_time = (suseconds_t) (1000000 * tv.tv_sec + tv.tv_usec);

    while (!zctx_interrupted) {
        gettimeofday(&tv, NULL);

        current_time = (suseconds_t) (1000000 * tv.tv_sec + tv.tv_usec);

        time_difference = current_time - last_time;

        // if (time_difference >= 25) {
            last_time = current_time;

            advance_buffer(file, buffer, block_cursor);

            zstr_sendm(socket, channel.c_str());

            if (block_cursor == block_count) {
                zmq_send(socket, buffer, file_size - (block_cursor - 1) * block_size, 0);
            } else {
                zmq_send(socket, buffer, block_size, 0);
            }

            if (block_cursor % 100 == 0) {
                std::cout << block_cursor * 100.0f / block_count << "%" << std::endl;
            }

            if (feof(file)) {
                return;
            }
        // }
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

long Publisher::get_file_size(std::string file_path)
{
    struct stat st;
    stat(file_path.c_str(), &st);
    return st.st_size;
}
