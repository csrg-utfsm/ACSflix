#include "ContextListener.hpp"

void ContextListener::set_interval(size_t milliseconds)
{
    this->milliseconds = (int) milliseconds;
}

ContextListener::ContextListener(int type) :
        context(zctx_new(), [](zctx_t * context) {
            zctx_destroy(&context);
        }),
        socket(zsocket_new(context.get(), type))
{

}

void ContextListener::wait_interval()
{
    if (milliseconds != 0) {
        zclock_sleep(milliseconds);
    }
}
