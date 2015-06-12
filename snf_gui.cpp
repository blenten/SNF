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

    QMenuBar* bar=new QMenuBar();
    ui->menuLayout->addWidget(bar);
    QMenu* langMenu=new QMenu("Language");
    bar->addMenu(langMenu);
    QAction* langRu,* langEn;
    langRu=new QAction("Русский", this);
    langEn=new QAction ("English", this);

    connect (langRu, SIGNAL(triggered()), this, SLOT (on_langRu_clicked()));
    connect (langEn, SIGNAL(triggered()), this, SLOT (on_LangEn_clicked()));

    langMenu->addAction(langEn);
    langMenu->addAction(langRu);
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

void SNF_gui::on_LangEn_clicked()
{
   setLocale("en_US");
}

void SNF_gui::on_langRu_clicked()
{
    setLocale("ru_RU");
}

void SNF_gui::setLocale (QString locale)
{
    Localizator l;
    l.loadLocale(locale);
    this->setWindowTitle(l.map["NoOperandsAndVariables"]);
}
