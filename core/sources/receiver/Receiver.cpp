#include <iostream>
#include <fstream>
#include "Receiver.hpp"

Receiver::Receiver(std::string ip) :
    credits(10)
{
    context = zctx_new();

    char identity[] = "S";

    // prepare the flow control channel.
    dealer = zsocket_new(context, ZMQ_DEALER);
    zsocket_connect(dealer, ("tcp://" + ip + ":6000").c_str());
    zsocket_set_identity(dealer, identity);

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
    zstr_sendm(dealer, "R");
    zstr_sendm(dealer, "");
    zstr_send(dealer, "HOLA");
}

void Receiver::receive_sets()
{
    std::cout << "[SETS] waiting for packet." << std::endl;
    zmsg_t * message = zmsg_recv(dealer);

    // delete identity.
    delete zmsg_popstr(message);

    // delete delimiter.
    delete zmsg_popstr(message);

    char * block_size_str = zmsg_popstr(message);
    std::cout << "[SETS] packet received." << std::endl;
    std::cout << "[SETS] block_size: " << block_size_str << std::endl;
    delete block_size_str;

    zmsg_destroy(&message);
}

void Receiver::start(std::string file_path, std::string channel)
{
    subscribe(channel);

    FILE * file = fopen(file_path.c_str(), "wb");

    zmsg_t * message;

    long blocks_received = 0;

    send_hola();
    receive_sets();

    while (!zctx_interrupted) {
        // send all available credits.
        while (credits) {
            zstr_send(dealer, "FETCH");
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
        consume(file, message);
        blocks_received++;
        credits++;

        // flush buffer to the real system file.
        fflush(file);

        zmsg_destroy(&message);
    }

    fclose(file);
}

void Receiver::subscribe(std::string channel)
{
    zsocket_set_subscribe(subscriber, const_cast<char*>(channel.c_str()));
    std::cout << "Subscribed to " << channel << std::endl;
}

void Receiver::consume(FILE * file, zmsg_t * message)
{
    zframe_t * frame = zmsg_pop(message);
    byte * buffer = zframe_data(frame);
    size_t content_size = zframe_size(frame);

    fwrite(buffer, 1, content_size, file);

    zframe_destroy(&frame);
}

void Receiver::set_credits(size_t credits)
{
    this->credits = credits;
}
