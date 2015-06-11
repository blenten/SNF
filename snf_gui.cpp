#include "snf_gui.h"


void SNF_gui::sleep(unsigned int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


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
    QTime time = QTime::currentTime();
    int val=0;

    qsrand((uint)time.msec());

    ui->conditionLabel->setText("Парсинг...");
    sleep(100 + qrand()%50);
    if(snf.parse(input.toStdString()))
    {
        ui->conditionLabel->setText("Неудачно.");
        ui->outputLine->setText("Ошибка ввода.");
        log = snf.getLog().c_str();
        return;
    }
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText("Склейка...");
    sleep(100 + qrand()%50);
    snf.match();
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText("Проверка избыточности...");
    sleep(100 + qrand()%50);
    snf.delNeedless();
    ui->progressBar->setValue(100);
    ///
    ui->conditionLabel->setText("Готово.");
    ui->outputLine->setText(snf.res_toString().c_str());
    log = snf.getLog().c_str();
}

void SNF_gui::on_stepsButton_clicked()
{
    Log *logform = new Log(this);
    logform->setlog(log);
    logform->show();
}
