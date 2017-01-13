#pragma once

#include "helper_macro.h"
#include "thread_console.h"

class ConsoleManager
{
    DECLARE_SINGLETON(ConsoleManager)

public:
    ConsoleThread *consoleThread;
};
