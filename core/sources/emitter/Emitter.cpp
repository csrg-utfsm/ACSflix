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

    // create the dealer to receiver credits from the client.
    dealer = zsocket_new(context, ZMQ_DEALER);
    zsocket_bind(dealer, "tcp://*:6000");

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
    std::cout << "[HOLA] waiting for packet." << std::endl;

    // delimiter.
    char * delimiter = zstr_recv(dealer);
    zstr_free(&delimiter);

    // code.
    char * code = zstr_recv(dealer);

    // check that this is a HOLA packet.
    if (strcmp(code, "HOLA") == 0) {
        std::cout << "[HOLA] packet received." << std::endl;
    } else {
        throw std::runtime_error("Invalid HOLA packet, probably out of sync.");
    }

    zstr_free(&code);
}

void Emitter::send_sets()
{
    std::string message = bdt::size_to_str(block_size);
    zstr_sendm(dealer, "");
    zstr_send(dealer, message.c_str());
    std::cout << "[SETS] packet sent." << std::endl;
}

void Emitter::receive_chao()
{
    char * id;
    while (true) {
        // analyze packet id, ignoring CREA packets.
        id = zstr_recv(dealer);

        if (strcmp(id, "CREA") == 0) {
            zstr_free(&id);
            continue;
        } else if (strcmp(id, "CHAO") == 0) {
            zstr_free(&id);
            break;
        } else {
            zstr_free(&id);
            // state error,
            throw std::runtime_error("Invalid CHAO/CREA packet, probably out of sync.");
        }
    }

    // blocks_received.
    char * blocks_received = zstr_recv(dealer);
    std::cout << "[CHAO] received got " << blocks_received << " packets." << std::endl;
    zstr_free(&blocks_received);
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
        // receive credit.
        delete zstr_recv(dealer);

        advance_buffer(file, buffer, block_cursor);

        zstr_sendm(publisher, channel.c_str());

        if (block_cursor == block_count) {
            this_size = file_size - (block_cursor - 1) * block_size;
        }

        zmq_send(publisher, buffer, this_size, 0);

        if (block_cursor % 100 == 0) {
            bar.set_cursor((size_t) block_cursor);
        }

        if (feof(file)) {
            // clear progress bar.
            std::cout << std::endl;

            // send DONE packet.
            zstr_sendm(publisher, channel.c_str());
            zstr_send(publisher, "");
            break;
        }
    }

    fclose(file);

    receive_chao();
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
