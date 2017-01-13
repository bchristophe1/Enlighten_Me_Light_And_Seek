#include "skeleton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Skeleton w;
    w.show();

    return a.exec();
}
