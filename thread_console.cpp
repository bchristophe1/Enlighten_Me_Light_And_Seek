#include "thread_console.h"

#include <QDebug>

#include "helper_settings.h"

ConsoleThread::ConsoleThread() { }

void ConsoleThread::run()
{
    _stopRequested = false;

    while(!_consoleBuffer.isEmpty() && !_stopRequested)
    {
        QChar ch = _consoleBuffer[0];

        // Insert a HTML tag if '@' is found
        if (ch == QChar('@') && _consoleBuffer[1] != QChar('@'))
        {
            _consoleBuffer.remove(0, 1);
            ch = _consoleBuffer[0];

            switch (ch.toLatin1())
            {
                case ConsoleTextType::ERROR:
                    emit newElement("<span style='color:red;'>Error:</span> ", true);
                    break;
                case ConsoleTextType::WARNING:
                    emit newElement("<span style='color:yellow;'>Warning:</span> ", true);
                    break;
                case ConsoleTextType::ACTION:
                    emit newElement("<span style='color:lime;'>Action:</span> ", true);
                    break;
                case ConsoleTextType::DEFAULT:
                    emit newElement("<span style='color:white;'>Information:</span> ", true);
                    break;
                case ConsoleTextType::BLUETOOTH:
                    emit newElement("<span style='color:cyan;'>Bluetooth: </span> ", true);
                    break;
                default:
                    break;
            }

            _consoleBuffer.remove(0, 1);
            continue;
        }
        else {
            _consoleBuffer.remove(0, 1);

            emit newElement(ch, false);

            QThread::msleep(CONSOLE_PRINT_CHAR_DELAY);
        }
    }
}

void ConsoleThread::AppendConsoleBuffer(QString str, ConsoleTextType type)
{
    qDebug() << str;

    _consoleBuffer += QString("@") + QChar(type);
    _consoleBuffer += str;

    if(!isRunning())
        start();
}

void ConsoleThread::SetConsoleBuffer(QString str, ConsoleTextType type)
{
    qDebug() << str;

    _consoleBuffer = "";

    AppendConsoleBuffer(str, type);
}

void ConsoleThread::Stop()
{
    _stopRequested = true;

    quit();
    wait();
}
