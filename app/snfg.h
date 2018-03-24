#ifndef SNFG_H
#define SNFG_H

#include <QMainWindow>
#include "ui_snfg.h"
#include "snf_minimizer/snf_minimizer.h"
#include "qmm/qm_minimizer.h"
#include "localizator/localizator.h"

#include <QTime>

#include "log.h"
#include "help.h"

namespace Ui
{
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
    void sleep (int ms);

    void on_minimizeButton_clicked();

    void minimizeAlgebraic();
    void minimizeQuine();

    void on_stepsButton_clicked();

    void langEn_clicked();
    void langRu_clicked();
    void help_clicked();

private:
    Ui::SNFG *ui;

    QString log;
    bool logShown = false;

    void setLocale (QString locale);

private slots:
    void receiveCondition(QString condition);
    void receiveLog(QString log);
    void receiveSleep(int ms);
    void receiveProgress(int val);
};

#endif // SNFG_H
