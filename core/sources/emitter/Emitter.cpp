#include <iostream>
#include <fstream>
#include <cmath>

#include "Emitter.hpp"
#include "../util/utils.h"
#include "../util/ProgressBar.hpp"

Emitter::Emitter() :
        block_size(16)
{
    context = zctx_new();

    // create the router to receiver credits from the client.
    router = zsocket_new(context, ZMQ_PAIR);
    zsocket_bind(router, "tcp://*:6000");

    // create the outgoing socket for binary data.
    publisher = zsocket_new(context, ZMQ_PUB);
    zsocket_bind(publisher, "tcp://*:5678");
}

Emitter::~Emitter()
{
    zctx_destroy(&context);
}

void Emitter::receive_hola()
{
    zmsg_t * message = zmsg_recv(router);

    // delete identity, it won't be used.
    delete zmsg_popstr(message);

    // delete delimiter.
    delete zmsg_popstr(message);

    char * code = zmsg_popstr(message);

    if (!strcmp(code, "HOLA")) {
        std::cout << "[HOLA] packet received." << std::endl;
    }

    delete code;

    zmsg_destroy(&message);
}

void Emitter::send_sets()
{
    std::string message = bdt::size_to_str(block_size);
    zstr_sendm(router, "S");
    zstr_sendm(router, "");
    zstr_send(router, message.c_str());
    std::cout << "[SETS] packet sent." << std::endl;
}

void Emitter::start(std::string file_path, std::string channel)
{
    FILE *file = fopen(file_path.c_str(), "rb");
    assert(file);

    long file_size = get_file_size(file_path);
    long block_count = (long) ceil((float) file_size / block_size);

    ProgressBar bar((size_t) block_count);

    long block_cursor = 0;
    byte buffer[block_size];

    size_t this_size = block_size;

    std::cout << "Blocks: " << block_count << std::endl;
    std::cout << "Waiting for client..." << std::endl;

    receive_hola();
    send_sets();

    while (!zctx_interrupted) {
        zframe_t * identify = zframe_recv(router);

        if (!identify) {
            break;
        }

        // receive credit.
        delete zstr_recv(router);

        advance_buffer(file, buffer, block_cursor);

        zstr_sendm(publisher, channel.c_str());

        if (block_cursor == block_count) {
            this_size = file_size - (block_cursor - 1) * block_size;
        }

        zmq_send(publisher, buffer, this_size, 0);

        if (block_cursor % 100 == 0) {
            bar.set_cursor((size_t) block_cursor);
            std::cout << block_cursor * 100.0f / block_count << "%" << std::endl;
        }

        if (feof(file)) {
            return;
        }
    }

    fclose(file);
}

void Emitter::set_block_size(size_t block_size)
{
    this->block_size = block_size;
}

void Emitter::advance_buffer(FILE *file, void *buffer, long &block_cursor)
{
    memset(buffer, 0, block_size);
    fread(buffer, 1, block_size, file);
    block_cursor++;
}

long Emitter::get_file_size(std::string file_path)
{
    struct stat st;
    stat(file_path.c_str(), &st);
    return st.st_size;
}
