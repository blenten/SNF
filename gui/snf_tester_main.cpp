/**
  \file
*/

#include  "gui/snf_tester_gui.h"
#include <QApplication>

/**
 * @brief main
 *
 * Точка входа приложения
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, char* argv[])
{
    QApplication a(argc, argv);
    SNF_Tester_gui w;
    w.show();

    return a.exec();
}
