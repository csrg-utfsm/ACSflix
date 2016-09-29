#include <iostream>
#include <google/protobuf/stubs/common.h>
#include "Worker.h"

int main(int argc, char* argv[])
{
    std::string identity;
    std::cin >> identity;

    Worker worker("tcp://127.0.0.1:8080", identity);

	while (worker.workPieces()) {
		//worker.workMSG();
	}

    return 0;
}
