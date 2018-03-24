#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "localizator/localizator.h"
#include "ui_log.h"

//logging class. Contains steps (some of steps represented by their name which will translate each time)
namespace Ui
{
class Log;
}

class Log : public QDialog
{
    Q_OBJECT
    friend class Localizator;

public:
    explicit Log(QWidget *parent = 0);
    ~Log();
    void setlog(QString);

private:
    Ui::Log *ui;
    QString log;

};

#endif // LOG_H
