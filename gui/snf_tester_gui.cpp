#include "snf_tester_gui.h"
#include "ui_snf_tester_gui.h"

SNF_Tester_gui::SNF_Tester_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNF_Tester_gui)
{
    ui->setupUi(this);
}

SNF_Tester_gui::~SNF_Tester_gui()
{
    delete ui;
}
