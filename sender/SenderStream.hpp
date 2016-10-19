#ifndef BDT_ENGINE_SENDERSTREAM_HPP
#define BDT_ENGINE_SENDERSTREAM_HPP


#include <string>
#include <map>
#include "ProtobufSender.h"

class SenderStream
{
private:
    /**
     * Storage of all flows.
     */
    std::map<std::string, ProtobufSender*> flows;

    /**
     * A buffer pool dependency used for flows.
     */
    BufferPool & pool;

    /**
     * Linger time as specified in a Flow.
     */
    int linger;

public:
    /**
     * Creates a Sender Stream, given a pool and a linger time.
     *
     * @param pool a pool as a dependency.
     * @param linger the linger time.
     */
    SenderStream(BufferPool & pool, int linger);

    ~SenderStream();

    /**
     * Creates a flow with a name that will be bound to this stream.
     *
     * @param flow_name name assigned to the flow.
     * @param connect connect string.
     * @return the created flow.
     */
    ProtobufSender * create_flow(std::string flow_name, std::string connect);

    /**
     * Returns the flow for the given name.
     *
     * @param name name of the flow to get.
     * @return the flow, or NULL.
     */
    ProtobufSender * get_flow(std::string name);

    /**
     * Checks if a flow exists.
     */
    bool exist_flow(std::string name);
};


#endif //BDT_ENGINE_SENDERSTREAM_HPP
