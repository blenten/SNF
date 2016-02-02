/**
  \file
  */

#include "gui/snfg.h"
#include <QApplication>

/**
 * @brief main
 *
 * Точка входа приложения
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SNFG w;
    w.show();

    return a.exec();
}
