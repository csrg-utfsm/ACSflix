
#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>
#include <memory>
#include <functional>
#include <vector>


class Receiver
{
private:
    std::function<void(zmsg_t*)> deleter = [](zmsg_t * message) {
        zmsg_destroy(&message);
    };

    void consume(FILE * file, zmsg_t * message);

    zctx_t * context;

    void * subscriber;
    void * dealer;

    size_t credits;

public:
    Receiver(std::string ip);

    ~Receiver();

    void subscribe(std::string channel);

    void start(std::string file_path, std::string channel);

    void set_credits(size_t credits);
};


#endif //PUBLISHER_SUBSCRIBER_HPP
