#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
}

void Log::setlog(QString l)
{
    this->setWindowTitle(Localizator::instance().getTranslation("%LogTitle"));
    ui->logText->setText(translateLog(l));
}

Log::~Log()
{
    delete ui;
}

QString Log::translateLog (const QString &l)
{
    QString output;
    QStringList list= l.split('\n');

    for (QStringList::iterator iter=list.begin();iter<list.end();iter++)
    {
        QStringList currList=(*iter).split('@');

        (*iter)= Localizator::instance().getTranslation(currList[0]);

        if (currList.size()>1) (*iter)+=currList[1]; // if input string has "@" delim and symbols after it (ex: %SomeError@SomePosition)

        output+=(*iter);
        if (iter!=list.end()-1) output+="\n";
    }
    return output;
}
