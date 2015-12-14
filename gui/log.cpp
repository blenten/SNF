/**
  \file
  */

#include "gui/log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
}

void Log::setlog(QString l)
{
    log = l;
    Localizator::instance().localize(this);
}

Log::~Log()
{
    delete ui;
}
