#include "snf_gui.h"
#include "ui_snf_gui.h"

#include "classes/snf_minimizer/snf_minimizer.h"

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
    QString output((snf.minimize(input.toStdString())).c_str());
    ui->outputLine->setText(output);
}
