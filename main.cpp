#include "gui/snf_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SNF_gui w;
    w.show();

    return a.exec();
}
