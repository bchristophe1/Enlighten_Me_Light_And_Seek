#include "manager_console.h"

DEFINE_SINGLETON(ConsoleManager)

ConsoleManager::ConsoleManager()
{
    consoleThread = new ConsoleThread();
}

ConsoleManager::~ConsoleManager()
{
    consoleThread->Stop();

    delete consoleThread;
}
