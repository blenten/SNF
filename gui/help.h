/**
  \file
  */
#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include "classes/localizator/localizator.h"
#include <QDir>

namespace Ui {


class Help;
}

/**
 * @brief Help
 */
class Help: public QDialog
{
    Q_OBJECT
    friend class Localizator;

public:
    /**
     * @brief Help
     * @param parent
     */
    explicit Help(QWidget *parent = 0);
    /**
      @brief ~Help
      */
    ~Help();

private:
    Ui::Help *ui;

    /**
     * @brief showHelp
     */
    void showHelp();
};

#endif // HELP_H
