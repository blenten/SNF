#include "../localizator/localizator.h"
#include <iostream>

void Localizator::loadLocale(QString locale)
{
    QFile file(":locale/locale_"+locale+".xml");
    file.open(QIODevice::ReadOnly);
    QByteArray byte=file.readAll();
    file.close();

    QXmlStreamReader reader;
    reader.addData(byte);
    QString currName;
    while (!reader.atEnd() && !reader.hasError())
    {
         QXmlStreamReader::TokenType token = reader.readNext();
         if (token == QXmlStreamReader::StartDocument) continue;

         if (reader.name()=="Main" || reader.name()=="Exception" || reader.name()=="Log") continue;

         if (reader.name().toString().trimmed()!="")
            currName= reader.name().toString();

         if (reader.text().toString().trimmed()!="")
             map.insert(currName, reader.text().toString());
    }
}

QString Localizator::getTranslation(QString name)
{
    if (name[0]!='%') return name;
    name.remove(0,1);
    return map[name];
}

QString Localizator::translateLog (const QString &l)
{
    QString output;
    QStringList list= l.split('\n');

    for (QStringList::iterator iter=list.begin();iter<list.end();iter++)
    {
        QStringList currList=(*iter).split('@');

        (*iter)= getTranslation(currList[0]);

        if (currList.size()>1) (*iter)+=currList[1]; // if input string has "@" delim and symbols after it (ex: %SomeError@SomePosition)

        output+=(*iter);
        if (iter!=list.end()-1) output+="\n";
    }
    return output;
}

void Localizator::localize(SNF_gui *window)
{
    window->ui->label_2->setText(getTranslation("%InputLabel"));
    window->ui->label->setText(getTranslation("%OutputLabel"));
    window->ui->minimizeButton->setText(getTranslation("%MinimizeButton"));
    window->ui->stepsButton->setText(getTranslation("%StepsButton"));
    window->ui->conditionLabel->setText(getTranslation("%ConditionDefault"));

    window->setWindowTitle(getTranslation("%Title"));
}

void Localizator::localize(Log *window)
{
    window->ui->logText->setText(translateLog(window->log));

    window->setWindowTitle(getTranslation("%LogTitle"));
}
