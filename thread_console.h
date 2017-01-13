#pragma once

#include <QThread>

#include "helper_settings.h"

class ConsoleThread : public QThread
{
    Q_OBJECT

public:
    ConsoleThread();

    virtual void run();

    void AppendConsoleBuffer(QString str, ConsoleTextType type = ConsoleTextType::DEFAULT);
    void SetConsoleBuffer(QString str, ConsoleTextType type = ConsoleTextType::DEFAULT);
    void Stop();

private:
    QString _consoleBuffer;
    bool _stopRequested;

signals:
    void newElement(QString str, bool isHTMLTag);
};
