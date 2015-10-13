#ifndef SNF_TESTER_GUI_H
#define SNF_TESTER_GUI_H

#include <QMainWindow>
#include "classes/snf_tester/snf_tester.h"

namespace Ui {
class SNF_Tester_gui;
}

class SNF_Tester_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit SNF_Tester_gui(QWidget *parent = 0);
    ~SNF_Tester_gui();

private:
    Ui::SNF_Tester_gui *ui;
};

#endif // SNF_TESTER_GUI_H
