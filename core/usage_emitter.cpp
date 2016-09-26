#include <iostream>

#include "sources/emitter/Emitter.hpp"

FILE * file_open(std::string file_path)
{
    FILE * file = fopen(file_path.c_str(), "rb");
    assert(file);
    return file;
}

size_t file_size(std::string file_path)
{
    struct stat st;
    stat(file_path.c_str(), &st);
    return (size_t) st.st_size;
}

int main(int argc, char* argv[])
{
    FILE * file = file_open("test.bin");
    size_t size = file_size("test.bin");

    Emitter emitter;

    // set some emitter parameters.
    emitter.set_block_size(1024 * 64);
    emitter.set_block_count_from_size(size);

    // starts the connection.
    emitter.start("A");

    // use the internal buffer from the emitter.
    byte * buffer = emitter.get_buffer();

    // send a chunk of data.
    while (!feof(file)) {
        // read the file contents and store to buffer.
        memset(buffer, 0, emitter.get_block_size());
        size_t sent_size = fread(buffer, 1, emitter.get_block_size(), file);

        // send the buffered data with the read size.
        emitter.send(buffer, sent_size);
    }

    fclose(file);

    // initiate the stop steps of the protocol.
    emitter.stop();

    return 0;
}
