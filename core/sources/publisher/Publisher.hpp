#ifndef PUBLISHER_PUBLISHER_HPP
#define PUBLISHER_PUBLISHER_HPP

#include <memory>
#include <string>
#include <czmq.h>

#include "../ContextListener.hpp"

class Publisher : public ContextListener
{
private:
    size_t block_size = 16;

    /**
     * @brief Moves cursor in the input stream and stores the block in the buffer.
     *
     * Moves the cursor of the stream in order to buffer another section of the
     * file given by the block_size.
     */
    void advance_buffer(std::ifstream & in, char *buffer, std::streamoff &offset);

public:
    Publisher(std::string ip);

    void start(std::string file_path, std::string channel);

    /**
     * @brief sets the block_size of data to transmit in one ZeroMQ message.
     *
     * Sets the block_size of data to transmit in one ZeroMQ Message, note that
     * ZeroMQ then fragments the data in frames, this block_size is not
     * necessary one frame, it just describes a sufficient piece of information
     * that the subscriber can consume and interpret.
     */
    void set_block_size(size_t block_size);
};


#endif //PUBLISHER_PUBLISHER_HPP
