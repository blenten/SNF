#include "snf_gui.h"


void SNF_gui::sleep(unsigned int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void SNF_gui::createMenubar()
{
    QMenuBar* bar=new QMenuBar();
    ui->menuLayout->addWidget(bar);

    QMenu* langMenu=new QMenu("Language");
    bar->addMenu(langMenu);

    QAction* langRu,* langEn;
    langEn=new QAction ("English", this);
    langRu=new QAction("Русский", this);

    connect (langEn, SIGNAL(triggered()), this, SLOT (langEn_clicked()));
    connect (langRu, SIGNAL(triggered()), this, SLOT (langRu_clicked()));

    langMenu->addAction(langEn);
    langMenu->addAction(langRu);
}

SNF_gui::SNF_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SNF_gui)
{
    ui->setupUi(this);

    Localizator::instance().loadLocale("ru_RU");
    this->setWindowTitle(Localizator::instance().getTranslation("%Title"));
    createMenubar();
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

    ui->progressBar->setValue(0);
    ui->conditionLabel->setText(Localizator::instance().getTranslation("%ConditionParsing"));
    sleep(100 + qrand()%50);
    if(snf.parse(input.toStdString()))
    {
        ui->conditionLabel->setText(Localizator::instance().getTranslation("%ConditionError"));
        ui->outputLine->setText(Localizator::instance().getTranslation("%ConditionError"));
        log = snf.getLog().c_str();
        return;
    }
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText(Localizator::instance().getTranslation("%ConditionMatch"));
    sleep(100 + qrand()%50);
    snf.match();
    val += 30 + qrand()%14;
    ui->progressBar->setValue(val);
    ///
    ui->conditionLabel->setText(Localizator::instance().getTranslation("%ConditionNessessity"));
    sleep(100 + qrand()%50);
    snf.delNeedless();
    ui->progressBar->setValue(100);
    ///
    ui->conditionLabel->setText(Localizator::instance().getTranslation("%ConditionReady"));
    ui->outputLine->setText(snf.res_toString().c_str());
    log = snf.getLog().c_str();
}

void SNF_gui::on_stepsButton_clicked()
{
    Log *logform = new Log(this);
    logform->setlog(log);
    logform->show();
}

void SNF_gui::langEn_clicked()
{
   setLocale("en_US");
}

void SNF_gui::langRu_clicked()
{
    setLocale("ru_RU");
}

void SNF_gui::setLocale (QString locale)
{
   Localizator::instance().loadLocale(locale);
   Localizator::instance().localize(this->ui);
   this->setWindowTitle(Localizator::instance().getTranslation("%Title"));
}
