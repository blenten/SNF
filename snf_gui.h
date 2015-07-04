#ifndef SNF_GUI_H
#define SNF_GUI_H

#include <QWidget>
#include <QMenuBar>
#include "ui_snf_gui.h"
#include "classes/snf_minimizer/snf_minimizer.h"
#include "classes/localizator/localizator.h"

#include <QTime>

#include "log.h"


namespace Ui {
class SNF_gui;
}

class SNF_gui : public QWidget
{
    Q_OBJECT
    friend class Localizator;

public:
    explicit SNF_gui(QWidget *parent = 0);
    ~SNF_gui();

private slots:
    void on_minimizeButton_clicked();

    void langEn_clicked();
    void langRu_clicked();

    void on_stepsButton_clicked();

    void sleep (unsigned int ms);

private:
    Ui::SNF_gui *ui;
    QString log;
    bool logShown=false;
    void setLocale (QString locale);
    void createMenubar();
};

#endif // SNF_GUI_H
