#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    showHelp();
}

Help::~Help()
{
    delete ui;
}

void Help::showHelp()
{
    ui->helpBrowser->setSource(QApplication::applicationDirPath()+"/help/index.htm");
}
