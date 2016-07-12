#include <iostream>
#include <fstream>
#include "Subscriber.hpp"

Subscriber::Subscriber(std::string ip)
{
    context = zctx_new();

    // prepare the flow control channel.
    dealer = zsocket_new(context, ZMQ_DEALER);
    zsocket_connect(dealer, "tcp://127.0.0.1:6000");

    // prepare the transport channel.
    subscriber = zsocket_new(context, ZMQ_SUB);
    zsocket_connect(subscriber, ("tcp://" + ip + ":5678").c_str());
}

Subscriber::~Subscriber()
{
    zctx_destroy(&context);
}

void Subscriber::start(std::string file_path, std::string channel)
{
    subscribe(channel);

    FILE * file = fopen(file_path.c_str(), "wb");

    std::unique_ptr<zmsg_t, decltype(deleter)> message(nullptr, deleter);

    long blocks_received = 0;

    while (!zctx_interrupted) {
        // send all available credits.
        while (credits) {
            zstr_send(dealer, "FETCH");
            credits--;
        }

        message.reset(zmsg_recv(subscriber));

        if (message.get() == nullptr) {
            continue;
        }

        // take out the channel code.
        zframe_t * channel_frame = zmsg_pop(message.get());
        zframe_destroy(&channel_frame);

        // given the architecture of the software, all messages
        // consist on only just one frame.
        consume(file, message.get());
        blocks_received++;
        credits++;

        // flush buffer to the real system file.
        fflush(file);
    }

    fclose(file);
}

void Subscriber::subscribe(std::string channel)
{
    zsocket_set_subscribe(subscriber, const_cast<char*>(channel.c_str()));
    std::cout << "Subscribed to " << channel << std::endl;
}

void Subscriber::consume(FILE * file, zmsg_t * message)
{
    zframe_t * frame = zmsg_pop(message);
    byte * buffer = zframe_data(frame);
    size_t content_size = zframe_size(frame);

    fwrite(buffer, 1, content_size, file);

    zframe_destroy(&frame);
}

void Subscriber::set_credits(size_t credits)
{
    this->credits = credits;
}

