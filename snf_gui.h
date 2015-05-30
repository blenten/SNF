#ifndef SNF_GUI_H
#define SNF_GUI_H

#include <QWidget>

namespace Ui {
class SNF_gui;
}

class SNF_gui : public QWidget
{
    Q_OBJECT

public:
    explicit SNF_gui(QWidget *parent = 0);
    ~SNF_gui();

private slots:
    void on_minimizeButton_clicked();

    void on_stepsButton_clicked();

private:
    Ui::SNF_gui *ui;
    QString log;
    bool logShown=false;
};

#endif // SNF_GUI_H
