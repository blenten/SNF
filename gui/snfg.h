#ifndef SNFG_H
#define SNFG_H

#include <QMainWindow>
#include "ui_snfg.h"
#include "classes/snf_minimizer/snf_minimizer.h"
#include "classes/localizator/localizator.h"

#include <QTime>

#include "log.h"
#include "help.h"



namespace Ui {
class SNFG;
}

class SNFG : public QMainWindow
{
    Q_OBJECT
    friend class Localizator;

public:
    explicit SNFG(QWidget *parent = 0);
    ~SNFG();

private slots:
    void sleep (unsigned int ms);

    void on_minimizeButton_clicked();
    void on_stepsButton_clicked();

    void langEn_clicked();
    void langRu_clicked();
    void help_clicked();

private:
    Ui::SNFG *ui;

    QString log;
    bool logShown = false;

    void setLocale (QString locale);
};

#endif // SNFG_H
