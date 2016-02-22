#include "snf_tester_gui.h"
#include "ui_snf_tester_gui.h"

SNF_Tester_gui::SNF_Tester_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNF_Tester_gui)
{
    ui->setupUi(this);
    this->setWindowTitle("SNF Tester " + QString(SNF_version));

    setInputValidators();
    connect (&tester, SIGNAL(onInfoSend(QString)), this, SLOT(getInfo(QString)));

    tester.moveToThread(&testerThread);
    connect (&testerThread, SIGNAL(started()), &tester, SLOT(start()));
    connect (&tester, SIGNAL(finish()), &testerThread, SLOT(quit()));
    connect (this, SIGNAL(stopTesting()), &tester, SLOT(stop()), Qt::DirectConnection);
}

void SNF_Tester_gui::setInputValidators()
{
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("[0-9]*"), this);

    ui->downVariablesNumber->setValidator(validator);
    ui->upVariablesNumber->setValidator(validator);
    ui->downOperandsNumber->setValidator(validator);
    ui->upOperandsNumber->setValidator(validator);
    ui->variablesStep->setValidator(validator);
    ui->operandsStep->setValidator(validator);
}

void SNF_Tester_gui::on_testButt_clicked()
{
    setTesterData();
    testerThread.start();
}

void SNF_Tester_gui::setTesterData()
{
    tester.downVariablesNumber = ui->downVariablesNumber->text().toUInt();
    tester.upVariablesNumber = ui->upVariablesNumber->text().toUInt();
    tester.downOperandsNumber = ui->downOperandsNumber->text().toUInt();
    tester.upOperandsNumber = ui->upOperandsNumber->text().toUInt();
    tester.variablesStep = ui->variablesStep->text().toUInt();
    tester.operandsStep = ui->operandsStep->text().toUInt();
    tester.logPath = ui->filename->text().toStdString();
}

void SNF_Tester_gui::getInfo(QString info)
{
    ui->textBrowser->setText(info);
}

SNF_Tester_gui::~SNF_Tester_gui()
{
    delete ui;
}

void SNF_Tester_gui::on_stopButt_clicked()
{
   emit stopTesting();
}
