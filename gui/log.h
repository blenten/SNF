/**
  \file
  */
#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include "classes/localizator/localizator.h"
#include "ui_log.h"

//logging class. Contains steps (some of steps represented by their name which will translate each time)
namespace Ui {
class Log;
}

/**
 * @brief Log
 */
class Log : public QDialog
{
    Q_OBJECT
    friend class Localizator;

public:
    /**
     * @brief Log
     * @param parent
     */
    explicit Log(QWidget *parent = 0);
    /**
      @brief ~Log
      */
    ~Log();
    /**
     * @brief setlog
     */
    void setlog(QString);

private:
    Ui::Log *ui;
    QString log;

};

#endif // LOG_H
