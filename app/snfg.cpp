#include "snfg.h"
#include "ui_snfg.h"

SNFG::SNFG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SNFG)
{
    ui->setupUi(this);

    connect(ui->actionEng, SIGNAL(triggered()), this, SLOT(langEn_clicked()));
    connect(ui->actionRu, SIGNAL(triggered()), this, SLOT(langRu_clicked()));
    connect(ui->actionUguide, SIGNAL(triggered()), this, SLOT(help_clicked()));

    QActionGroup* methodGroup = new QActionGroup(this);

    QList<QAction*> methodActions = ui->menuMethod->actions();
    for (auto i = methodActions.begin();i<methodActions.end();i++)
        methodGroup->addAction(*i);

    Localizator::instance().loadLocale("ru_RU");
    Localizator::instance().localize(this);
}

SNFG::~SNFG()
{
    delete ui;
}

void SNFG::sleep(int ms)
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
    if (ui->actionAlgebraicManupulation->isChecked())
        minimizeAlgebraic();
    else if (ui->actionQuineMcCluskey->isChecked())
        minimizeQuine();
}

void SNFG::minimizeAlgebraic()
{
    this->log="";
    ui->progressBar->setValue(0);

    SNF_Minimizer snf;

    connect (&snf, SIGNAL(sendCondition(QString)), this, SLOT(receiveCondition(QString)));
    connect (&snf, SIGNAL(sendLog(QString)), this, SLOT(receiveLog(QString)));
    connect (&snf, SIGNAL(sendSleep(int)), this, SLOT(receiveSleep(int)));
    connect (&snf, SIGNAL(sendProgress(int)), this, SLOT(receiveProgress(int)));

    QString input = ui->inputText->toPlainText();
    ui->outputLine->setText(snf.minimize(input));

    disconnect (&snf, SIGNAL(sendCondition(QString)), this, SLOT(receiveCondition(QString)));
    disconnect (&snf, SIGNAL(sendLog(QString)), this, SLOT(receiveLog(QString)));
    disconnect (&snf, SIGNAL(sendSleep(int)), this, SLOT(receiveSleep(int)));
    disconnect (&snf, SIGNAL(sendProgress(int)), this, SLOT(receiveProgress(int)));
}

void SNFG::minimizeQuine()
{
    this->log="";
    ui->progressBar->setValue(0);

    QM_Minimizer qm;

    connect (&qm, SIGNAL(sendCondition(QString)), this, SLOT(receiveCondition(QString)));
    connect (&qm, SIGNAL(sendLog(QString)), this, SLOT(receiveLog(QString)));
    connect (&qm, SIGNAL(sendSleep(int)), this, SLOT(receiveSleep(int)));
    connect (&qm, SIGNAL(sendProgress(int)), this, SLOT(receiveProgress(int)));

    QString input = ui->inputText->toPlainText();
    ui->outputLine->setText(qm.minimize(input));

    disconnect (&qm, SIGNAL(sendCondition(QString)), this, SLOT(receiveCondition(QString)));
    disconnect (&qm, SIGNAL(sendLog(QString)), this, SLOT(receiveLog(QString)));
    disconnect (&qm, SIGNAL(sendSleep(int)), this, SLOT(receiveSleep(int)));
    disconnect (&qm, SIGNAL(sendProgress(int)), this, SLOT(receiveProgress(int)));
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

void SNFG::receiveCondition(QString condition)
{
    ui->conditionLabel->setText(Localizator::instance().translate(condition));
}

void SNFG::receiveLog(QString log)
{
    if (log=="") return;

    this->log+=log;
    this->log+="\n";
}
\
void SNFG::receiveSleep(int ms)
{
    sleep (ms);
}

void SNFG::receiveProgress(int val)
{
    ui->progressBar->setValue(val);
}
