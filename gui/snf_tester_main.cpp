#include  "gui/snf_tester_gui.h"
#include <QApplication>

int main (int argc, char* argv[])
{
    QApplication a(argc, argv);
    SNF_Tester_gui w;
    w.show();

    return a.exec();
}
