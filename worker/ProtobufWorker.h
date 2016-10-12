#ifndef BDT_ENGINE_PROTOBUFWORKER_H
#define BDT_ENGINE_PROTOBUFWORKER_H


#include <czmq.h>
#include <google/protobuf/message_lite.h>

class ProtobufWorker
{
private:
    zctx_t * context;

    void * dealer;

    // TODO: save working state for exit checks.

public:
    ProtobufWorker(std::string connect, std::string identity);

    ~ProtobufWorker();

    // TODO
    /**
     *
     * @param message
     * @return true if there's more work to do.
     *
     * @throws google::protobuf::FatalException if parsing fails.
     */
    bool work(google::protobuf::MessageLite & message);
};


#endif //BDT_ENGINE_PROTOBUFWORKER_H
