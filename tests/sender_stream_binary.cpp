#include <iostream>
#include <BytesSenderFlow.h>
#include <ctime>

#include "SenderStream.hpp"

int main(int argc, char * argv[])
{
    BufferPool pool;
    SenderStream stream(pool, 1000);

    BytesSenderFlow * flow1 = stream.create_flow<BytesSenderFlow>("Flow1", "tcp://*:9991");

    FILE * file = fopen(argv[1], "rb");
    assert(file);

    char buffer[4096]; // 4KB

    size_t sent_size;

    clock_t begin = clock();
    size_t block_count = 0;
    size_t accumulated_sent_size = 0;

    //std::cout << "Beginning transmission..." << std::endl;
    // sent_size == sizeof(buffer) except for the last package
    uint32_t i = 0;
    while (!feof(file)) {
        sent_size = fread(buffer, sizeof(char), sizeof(buffer), file);
        flow1->send(buffer, sent_size);

        block_count++;

        /*if (block_count % 256 == 0) {
	    std::cout << "Sent: " << block_count << " blocks of " << sent_size << " bytes each." << std::endl;
        }*/
	accumulated_sent_size += sent_size;
	//std::cout << "Accumulated: " << accumulated_sent_size << std::endl;
	std::cout << buffer;
    }

    clock_t end = clock();

    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;

    std::cerr << "\nSeconds: " << elapsed_secs << std::endl;

    flow1->stop();

    fclose(file);

    return 0;
}
