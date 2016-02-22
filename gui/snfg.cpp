#include "gui/snfg.h"
#include "ui_snfg.h"

SNFG::SNFG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNFG)
{
    ui->setupUi(this);

    connect(ui->actionEng, SIGNAL(triggered()), this, SLOT(langEn_clicked()));
    connect(ui->actionRu, SIGNAL(triggered()), this, SLOT(langRu_clicked()));
    connect(ui->actionUguide,SIGNAL(triggered()), this, SLOT(help_clicked()));

    Localizator::instance().loadLocale("ru_RU");
    Localizator::instance().localize(this);
}

SNFG::~SNFG()
{
    delete ui;
}

void SNFG::sleep(unsigned int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void SNFG::setLocale (QString locale)
{
   Localizator::instance().loadLocale(locale);
   Localizator::instance().localize(this);
}



void SNFG::on_minimizeButton_clicked()
{
    SNF_Minimizer snf;
    QString input = ui->inputText->toPlainText();

    QTime time = QTime::currentTime();
    int val = 0;
    qsrand((uint)time.msec());

    ui->progressBar->setValue(0);
    ui->conditionLabel->setText(Localizator::instance().translate("%ConditionParsing"));
    sleep(100 + qrand()%50);
    if(snf.parse(input.toStdString()))
    {
        ui->conditionLabel->setText(Localizator::instance().translate("%ConditionError"));
        ui->outputLine->setText(Localizator::instance().translate("%ConditionError"));
        log = snf.getLog().c_str();
        return;
    }
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText(Localizator::instance().translate("%ConditionMatch"));
    sleep(100 + qrand()%50);
    snf.match();
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText(Localizator::instance().translate("%ConditionNessessity"));
    sleep(100 + qrand()%50);
    snf.delUnness();
    ui->progressBar->setValue(100);
    ///
    ui->conditionLabel->setText(Localizator::instance().translate("%ConditionReady"));
    ui->outputLine->setText(snf.res_toString().c_str());
    log = snf.getLog().c_str();
}

void SNFG::on_stepsButton_clicked()
{
    Log *logform = new Log(this);
    logform->setlog(log);
    logform->show();
}

void SNFG::langEn_clicked()
{
   setLocale("en_US");
}

void SNFG::langRu_clicked()
{
    setLocale("ru_RU");
}

void SNFG::help_clicked()
{
    Help* helpform = new Help (this);
    helpform->show();
}
