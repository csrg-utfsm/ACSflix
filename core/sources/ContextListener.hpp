#ifndef PUBLISHER_CONTEXTLISTENERS_HPP
#define PUBLISHER_CONTEXTLISTENERS_HPP

#include <czmq.h>
#include <string>


class ContextListener
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

    int milliseconds;

protected:
    void * socket;

    void wait_interval();

public:
    ContextListener(int type);

    /**
     * @brief Starts sending data to subscribers, block by block.
     *
     * Sends binary data block by block, given by the block_size. This is a
     * blocking method, so you will probably need to thread this class in
     * order to have multiple publishers.
     */
    virtual void start(std::string file_path, std::string channel) = 0;

    /**
     * @brief Sets an interval between messages.
     *
     * In order to test more efficiently, it is convenient to have a time between
     * messages. This method sets an interval if needed, the default behaviour
     * is to send them all with no interruption, and can be achieved with an
     * interval of 0.
     */
    void set_interval(size_t milliseconds);
};


#endif //PUBLISHER_CONTEXTLISTENERS_HPP
