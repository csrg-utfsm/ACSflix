#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>
#include <memory>
#include "../ContextListener.hpp"


class Subscriber : public ContextListener
{
public:
    Subscriber(std::string ip);

    void start(std::string file_path, std::string channel);
};


#endif //PUBLISHER_SUBSCRIBER_HPP
