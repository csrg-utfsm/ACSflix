#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>

#include "Emitter.hpp"
#include "../util/utils.h"

Emitter::Emitter() :
        block_size(16),
        block_count(0),
        block_cursor(0),
        buffer(NULL)
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
    delete[] buffer;
}

void Emitter::send_sets()
{
    std::string message = bdt::size_to_str(block_size);
    zstr_sendm(dealer, "");
    zstr_send(dealer, message.c_str());
    std::cout << "[SETS] packet sent." << std::endl;
}

void Emitter::send_done()
{
    // send DONE packet.
    zstr_sendm(publisher, channel.c_str());
    zstr_send(publisher, "");
}

void Emitter::receive_hola()
{
    std::cout << "[HOLA] waiting for packet." << std::endl;

    // delimiter.
    delete zstr_recv(dealer);

    // code.
    char * code = zstr_recv(dealer);

    // check that this is a HOLA packet.
    if (strcmp(code, "HOLA") == 0) {
        std::cout << "[HOLA] packet received." << std::endl;
    } else {
        throw std::runtime_error("Invalid HOLA packet, probably out of sync.");
    }

    delete code;
}

void Emitter::receive_chao()
{
    char * id;
    while (true) {
        // analyze packet id, ignoring CREA packets.
        id = zstr_recv(dealer);

        if (strcmp(id, "CREA") == 0) {
            delete id;
            continue;
        } else if (strcmp(id, "CHAO") == 0) {
            delete id;
            break;
        } else {
            delete id;

            // state error.
            throw std::runtime_error("Invalid CHAO/CREA packet, probably out of sync.");
        }
    }

    // blocks_received.
    char * blocks_received = zstr_recv(dealer);
    std::cout << "[CHAO] received got " << blocks_received << " packets." << std::endl;
    delete blocks_received;
}

void Emitter::start(std::string channel)
{
    this->channel = channel;

    std::cout << "Blocks: " << block_count << std::endl;

    receive_hola();
    send_sets();
}

void Emitter::send(byte * buffer, size_t buffer_size)
{
    // receive credit.
    delete zstr_recv(dealer);

    block_cursor++;

    // send piece of data.
    zstr_sendm(publisher, channel.c_str());
    zmq_send(publisher, buffer, buffer_size, 0);
}

void Emitter::stop()
{
    send_done();
    receive_chao();
}

void Emitter::set_block_size(size_t block_size)
{
    this->block_size = block_size;

    // my compiler needed this cast...
    buffer = (byte *) malloc(block_size);
}

void Emitter::set_block_count(size_t block_count)
{
    this->block_count = block_count;
}

void Emitter::set_block_count_from_size(size_t file_size)
{
    set_block_count((size_t) ceil(file_size / block_size));
}

byte * Emitter::get_buffer()
{
    return buffer;
}

size_t Emitter::get_block_cursor()
{
    return block_cursor;
}

size_t Emitter::get_block_count()
{
    return block_count;
}

size_t Emitter::get_block_size()
{
    return block_size;
}
