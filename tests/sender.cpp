#include <iostream>

#include "ProtobufSender.h"
#include "Simple.pb.h"

int main()
{
    BufferPool pool;

    ProtobufSender sender("tcp://127.0.0.1:9999", pool);

    Simple simple;
    simple.set_message("rodolfoql");

    for (int i = 0; i < 20; ++i) {
        simple.set_id(i);
        sender.send(simple);
    }

    return 0;
}