#ifndef PUBLISHER_WORKER_H
#define PUBLISHER_WORKER_H

#include <czmq.h>
#include <string>

class Worker
{
private:
    zctx_t * context;
    void * dealer;

public:
    Worker(std::string connect, std::string identity);

    ~Worker();

    void work();
};


#endif //PUBLISHER_WORKER_H
