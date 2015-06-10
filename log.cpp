#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
}

void Log::setlog(QString l)
{
    ui->logText->setText(l);
}

Log::~Log()
{
    delete ui;
}
