#include "snf_tester_gui.h"
#include "ui_snf_tester_gui.h"

SNF_Tester_gui::SNF_Tester_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNF_Tester_gui)
{
    ui->setupUi(this);
    tester.moveToThread(&testerThread);

    connect (&tester, SIGNAL(onInfoSend(QString)), this, SLOT(getInfo(QString)));

    connect (&testerThread, SIGNAL(started()), &tester, SLOT(run()));
    connect (&tester, SIGNAL(finish()), &testerThread, SLOT(quit()));
}

SNF_Tester_gui::~SNF_Tester_gui()
{
    delete ui;
}

void SNF_Tester_gui::on_pushButton_clicked()
{
    testerThread.start();
}

void SNF_Tester_gui::getInfo(QString info)
{
    ui->textBrowser->setText(info);
}

