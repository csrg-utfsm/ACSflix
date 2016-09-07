#include <iostream>
#include <fstream>
#include "Receiver.hpp"
#include "../util/utils.h"

Receiver::Receiver(std::string ip) :
    credits(10)
{
    context = zctx_new();

    // prepare the connection and flow control channel.
    dealer = zsocket_new(context, ZMQ_DEALER);
    zsocket_connect(dealer, ("tcp://" + ip + ":6000").c_str());

    // prepare the transport channel.
    subscriber = zsocket_new(context, ZMQ_SUB);
    zsocket_connect(subscriber, ("tcp://" + ip + ":5678").c_str());
}

Receiver::~Receiver()
{
    zctx_destroy(&context);
}

void Receiver::send_hola()
{
    zstr_sendm(dealer, "");
    zstr_send(dealer, "HOLA");
    std::cout << "[HOLA] packet sent." << std::endl;
}

void Receiver::receive_sets()
{
    std::cout << "[SETS] waiting for packet." << std::endl;

    // delimiter.
    char * delimiter = zstr_recv(dealer);
    if (delimiter == NULL) {
        exit(13);
    }

    std::cout << "[SETS] delimiter received." << std::endl;
    zstr_free(&delimiter);

    // block size.
    char * block_size_str = zstr_recv(dealer);
    std::cout << "[SETS] block_size: " << block_size_str << std::endl;
    zstr_free(&block_size_str);
}

void Receiver::send_chao()
{
    std::string message = bdt::size_to_str(blocks_received);
    zstr_sendm(dealer, "CHAO");
    zstr_send(dealer, message.c_str());
}

void Receiver::start(std::string file_path, std::string channel)
{
    subscribe(channel);

    FILE * file = fopen(file_path.c_str(), "wb");

    zmsg_t * message;

    blocks_received = 0;

    send_hola();
    receive_sets();

    while (!zctx_interrupted) {
        // send all available credits.
        while (credits) {
            zstr_send(dealer, "CREA");
            credits--;
        }

        message = zmsg_recv(subscriber);

        if (message == NULL) {
            continue;
        }

        // take out the channel code.
        zframe_t * channel_frame = zmsg_pop(message);
        zframe_destroy(&channel_frame);

        // given the architecture of the software, all messages
        // consist on only just one frame.
        zframe_t * frame = zmsg_pop(message);

        std::cout << zframe_size(frame) << std::endl;

        if (zframe_size(frame) == (size_t) 0) {
            // receive DONE packet is received, quit receiving.
            break;
        }

        consume(file, frame);
        blocks_received++;
        credits++;

        // flush buffer to the real system file.
        fflush(file);

        zframe_destroy(&frame);
        zmsg_destroy(&message);
    }

    fclose(file);

    send_chao();
}

void Receiver::subscribe(std::string channel)
{
    zsocket_set_subscribe(subscriber, const_cast<char*>(channel.c_str()));
    std::cout << "Subscribed to " << channel << std::endl;
}

void Receiver::consume(FILE * file, zframe_t * frame)
{
    byte * buffer = zframe_data(frame);
    size_t content_size = zframe_size(frame);

    fwrite(buffer, 1, content_size, file);
}

void Receiver::set_credits(size_t credits)
{
    this->credits = credits;
}
