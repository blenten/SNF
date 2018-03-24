#ifndef SNF_TESTER_GUI_H
#define SNF_TESTER_GUI_H

#include <QMainWindow>
#include "snf_tester/snf_tester.h"
#include "QThread"

namespace Ui {
class SNF_Tester_gui;
}

class SNF_Tester_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit SNF_Tester_gui(QWidget *parent = 0);
    ~SNF_Tester_gui();

private slots:
    void on_testButt_clicked();
    void getInfo(QString info);

    void on_stopButt_clicked();

signals:
    void stopTesting();

private:
    Ui::SNF_Tester_gui *ui;
    SNF_Tester tester;
    QThread testerThread;

    void setInputValidators();
    void setTesterData();
};

#endif // SNF_TESTER_GUI_H
