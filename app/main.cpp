#include "snfg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SNFG w;
    w.show();

    return a.exec();
}
