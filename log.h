#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "classes/localizator/localizator.h"

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
private:
    Ui::Log *ui;

};

#endif // LOG_H
