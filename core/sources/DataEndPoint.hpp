#ifndef PUBLISHER_DATAENDPOINT_HPP
#define PUBLISHER_DATAENDPOINT_HPP

#include <czmq.h>
#include <string>


class DataEndPoint
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
    DataEndPoint(int type);

    /**
     * @brief Starts the endpoint for sending or receiving data.
     *
     * Starts the endpoint for sending or receiving data, it is the
     * job of the implementing class to define the corresponding
     * behaviour.
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


#endif //PUBLISHER_DATAENDPOINT_HPP
