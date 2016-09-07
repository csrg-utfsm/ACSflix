#ifndef PUBLISHER_PUBLISHER_HPP
#define PUBLISHER_PUBLISHER_HPP

#include <memory>
#include <string>
#include <czmq.h>

class Emitter
{
private:
    size_t block_size;
    size_t block_count;
    size_t block_cursor;

    byte * buffer;

    std::string channel;
    zctx_t * context;
    void * publisher;
    void * dealer;

    void send_sets();

    void send_done();

    void receive_hola();

    void receive_chao();

public:
    Emitter();

    ~Emitter();

    /**
     * @brief Set start connection parameters and contacts the receiver.
     *
     * Initiates the handshake process and blocks until the first steps of
     * the protocols are done.
     */
    void start(std::string channel);

    /**
     * @brief sends a block of data to the receiver.
     *
     * Blocks until a credit is get and then sends the block asynchronously.
     * After the call to this function, the packet may or may not send the
     * block, since this is handled by ZeroMQ. But the Credits System will
     * make sure that the data arrives to the client as fast as it can handle.
     */
    void send(byte * buffer, size_t buffer_size);

    /**
     * @brief starts the stop process of the protocol.
     *
     * It sends the DONE packet and waits until the receiver responds with
     * a CHAO packet. This is a blocking operation.
     */
    void stop();

    /**
     * @param block_size one block size in bytes.
     */
    void set_block_size(size_t block_size);

    /**
     * @param block_count the total ammount of blocks.
     */
    void set_block_count(size_t block_count);

    /**
     * @param file_size sets the block_count by dividing the file_size in the
     *                  block_size.
     */
    void set_block_count_from_size(size_t file_size);

    byte * get_buffer();

    size_t get_block_size();

    size_t get_block_cursor();

    size_t get_block_count();
};


#endif //PUBLISHER_PUBLISHER_HPP
