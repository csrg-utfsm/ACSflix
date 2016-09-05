#ifndef PUBLISHER_PUBLISHER_HPP
#define PUBLISHER_PUBLISHER_HPP

#include <memory>
#include <string>
#include <czmq.h>

class Emitter
{
private:
    size_t block_size;

    zctx_t * context;

    void * publisher;
    void * router;

    /**
     * @brief Moves cursor in the input stream and stores the block in the buffer.
     *
     * Moves the cursor of the stream in order to buffer another section of the
     * file given by the block_size.
     */
    void advance_buffer(FILE * file, void * buffer, long & block_cursor);

    /**
     * @brief Obtains how many blocks are contained in the file.
     */
    long get_file_size(std::string file_path);

public:
    Emitter();

    ~Emitter();

    /**
     * @brief Starts sending data to subscribers, block by block.
     *
     * Sends binary data block by block, given by the block_size. This is a
     * blocking method, so you will probably need to thread this class in
     * order to have multiple publishers.
     */
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

    void send_sets();
};


#endif //PUBLISHER_PUBLISHER_HPP
