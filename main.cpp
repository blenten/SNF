#include "snf_gui.h"
#include "classes/snf_generator/snf_generator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    SNF_Generator::testMinimizing("log.txt", 1, 3, 1, 5, 1, 1, std::cerr);
    QApplication a(argc, argv);
    SNF_gui w;
    w.show();

    return a.exec();
}
