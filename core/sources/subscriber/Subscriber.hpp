#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>
#include <memory>
#include <functional>
#include <vector>

#include "../DataEndPoint.hpp"


class Subscriber : public DataEndPoint
{
private:
    std::function<void(zmsg_t*)> deleter = [](zmsg_t * message) {
        zmsg_destroy(&message);
    };

    void consume(FILE * file, zmsg_t * message);

public:
    Subscriber(std::string ip);

    void subscribe(std::string channel);

    void start(std::string file_path, std::string channel);
};


#endif //PUBLISHER_SUBSCRIBER_HPP
