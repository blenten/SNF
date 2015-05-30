#include "snf_gui.h"
#include "ui_snf_gui.h"

#include "classes/snf_minimizer/snf_minimizer.h"
#include <QDebug>

SNF_gui::SNF_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SNF_gui)
{
    ui->setupUi(this);
}

SNF_gui::~SNF_gui()
{
    delete ui;
}

void SNF_gui::on_minimizeButton_clicked()
{
    SNF_Minimizer snf;
    QString input = ui->inputText->toPlainText();
    ///
    ui->conditionLabel->setText("Parsing...");
    if(snf.parse(input.toStdString()))
    {
        ui->conditionLabel->setText("Failure.");
        ui->outputLine->setText("Input error.");
        log = snf.getLog().c_str();
        return;
    }
    ///
    ui->conditionLabel->setText("Matching...");
    snf.match();
    ///
    ui->conditionLabel->setText("Checking nesessity...");
    snf.delNeedless();
    ///
    ui->conditionLabel->setText("Done.");
    ui->outputLine->setText(snf.res_toString().c_str());
    log = snf.getLog().c_str();
}

void SNF_gui::on_stepsButton_clicked()
{
    qDebug()<<log;
}
