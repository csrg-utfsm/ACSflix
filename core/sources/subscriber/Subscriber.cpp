#include <iostream>
#include <fstream>
#include "Subscriber.hpp"

Subscriber::Subscriber(std::string ip) :
        DataEndPoint(ZMQ_SUB)
{
    // int size = 1024 * 512;
    // zmq_setsockopt(socket, ZMQ_RCVBUF, &size, sizeof(size));

    zsocket_connect(socket, ("tcp://" + ip + ":5678").c_str());
}

void Subscriber::start(std::string file_path, std::string channel)
{
    subscribe(channel);

    FILE * file = fopen(file_path.c_str(), "wb");

    std::unique_ptr<zmsg_t, decltype(deleter)> message(nullptr, deleter);

    long blocks_received = 0;

    while (!zctx_interrupted) {
        message.reset(zmsg_recv(socket));

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

        // flush buffer to the real system file.
        fflush(file);

        wait_interval();
    }

    fclose(file);
}

void Subscriber::subscribe(std::string channel)
{
    zsocket_set_subscribe(socket, const_cast<char*>(channel.c_str()));
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
