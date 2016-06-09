#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>
#include <memory>


class Subscriber
{
private:
    /**
     * @brief ZeroMQ context pointer.
     *
     * This pointer must be initialized with (zctx_new(), zctx_destroy) as parameters
     * in order to destroy the context. Note that zctx_destroy automatically destroys
     * all context sockets.
     */
    std::shared_ptr<zctx_t> context;

    void * socket;

public:
    Subscriber();

    void mainloop();
};


#endif //PUBLISHER_SUBSCRIBER_HPP
