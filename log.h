#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "classes/localizator/localizator.h"

//logging class. Contains steps (some of steps represented by their name which will translate each time)
namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0);
    ~Log();
    void setlog(QString);

    QString translateLog(const QString &l);
private:
    Ui::Log *ui;

};

#endif // LOG_H
