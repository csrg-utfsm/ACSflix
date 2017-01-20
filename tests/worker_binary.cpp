#include <iostream>
#include <WorkerStream.hpp>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <cassert>

class SampleWorkerFlowCallback : public WorkerFlowCallback
{
private:
public:
    virtual void on_start(WorkerFlow * flow)
	{

	}

    virtual void on_workload(char * buffer, size_t size)
	{
		FILE * file = fopen("test.jpg", "ab");
		assert(file);

		size_t  s = fwrite(buffer, 1, size, file);
		assert(s == size);

		fclose(file);
	}

    virtual void on_stop()
	{

	}
};


int main(int argc, char * argv[])
{
    if (argc != 4) {
	std::cout << "Usage: " << *argv << " name connect tokens" << std::endl;
	return 1;
    }

    WorkerStream stream;

    size_t tokens = (size_t) strtol(argv[3], NULL, 10); // Assume correct input

    std::string identity(argv[1], strlen(argv[1]));

    SampleWorkerFlowCallback callback;
    stream.create_flow(identity, argv[2], &callback, tokens);
    stream.start();

    return 0;
}
