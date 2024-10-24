#include "eventHandler.h"
void  IEventHandlerWrapper::exec(const Event& e)
    {
        call(e);
    }
