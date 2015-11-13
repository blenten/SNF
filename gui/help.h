#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include "classes/localizator/localizator.h"
#include <QDir>

namespace Ui {
class Help;
}

class Help: public QDialog
{
    Q_OBJECT
    friend class Localizator;

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

private:
    Ui::Help *ui;

    void showHelp();
};

#endif // HELP_H
