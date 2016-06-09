#ifndef PUBLISHER_PUBLISHER_HPP
#define PUBLISHER_PUBLISHER_HPP

#include <memory>

#include <czmq.h>

class Publisher
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
    Publisher();

    void mainloop();
};


#endif //PUBLISHER_PUBLISHER_HPP
