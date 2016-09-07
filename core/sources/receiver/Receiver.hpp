
#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>


class Receiver
{
private:
    zctx_t * context;

    void * subscriber;
    void * dealer;

    size_t blocks_received;
    size_t credits;

    void consume(FILE * file, zframe_t * message);

public:
    Receiver(std::string ip);

    ~Receiver();

    void subscribe(std::string channel);

    void start(std::string file_path, std::string channel);

    void set_credits(size_t credits);

    void receive_sets();

    void send_hola();

    void send_chao();
};


#endif //PUBLISHER_SUBSCRIBER_HPP
