#include "classes/localizator/localizator.h"
#include <iostream>

void Localizator::loadLocale(QString locale)
{
    QFile file(":locale/locale_" + locale + ".xml");
    file.open(QIODevice::ReadOnly);
    QByteArray byte = file.readAll();
    file.close();

    QXmlStreamReader reader;
    reader.addData(byte);
    QString currName;
    while (!reader.atEnd() && !reader.hasError())
    {
         QXmlStreamReader::TokenType token = reader.readNext();
         if (token == QXmlStreamReader::StartDocument) continue;

         if (reader.name()=="Main" || reader.name()=="Exception" || reader.name()=="Log" || reader.name()=="Help") continue;

         if (reader.name().toString().trimmed() != "")
            currName = reader.name().toString();

         if (reader.text().toString().trimmed() != "")
             map.insert(currName, reader.text().toString());
    }
}

void Localizator::localize(SNF_gui *window)
{
    window->ui->label_2->setText(translate("%InputLabel"));
    window->ui->label->setText(translate("%OutputLabel"));
    window->ui->minimizeButton->setText(translate("%MinimizeButton"));
    window->ui->stepsButton->setText(translate("%StepsButton"));
    window->ui->conditionLabel->setText(translate("%ConditionDefault"));

    window->setWindowTitle(translate("%Title", {QString(SNF_version)}));
}

void Localizator::localize(Help *window)
{
    window->setWindowTitle(translate("%HelpTitle"));
}

void Localizator::localize(Log *window)
{
    window->ui->logText->setText(translateLog(window->log));

    window->setWindowTitle(translate("%LogTitle"));
}

QString Localizator::translate(QString name, std::vector<QString> args)
{
    name = translate(name);
    name = insertArgsIntoString(name, args);

    return name;
}

QString Localizator::translate(QString name)
{
    if (name[0] != '%') return name;
    name.remove(0,1);
    return map[name];
}

QString Localizator::insertArgsIntoString (QString str, std::vector<QString> &args)
{
    for (int i=0;i<str.length();i++)
    {
        if (str.at(i)=='{')
        {
            size_t temp = i+1;
            QString argIndex;

            while (str.at(temp)!='}')
                argIndex+=str.at(temp++);

            str.remove(i, (temp-i+1));
            i--;

            size_t index = argIndex.toInt();

            if (index<args.size())
            {
                str.insert(i+1,args[index]);
                i+=args[index].length();
            }
        }
    }
    return str;
}

QString Localizator::translateLog (const QString &l)
{
    QString output;
    QStringList list= l.split('\n');

    for (QStringList::iterator iter=list.begin(); iter<list.end(); iter++)
    {
        QStringList strWithArgs = (*iter).split('@');
        QString str = strWithArgs[0];

        std::vector<QString> args;

        if (strWithArgs.size()>1)
           for (int i=1;i<strWithArgs.size();i++)
               args.push_back(translate(strWithArgs[i]));

        output+=translate(str, args);

        if (iter != list.end()-1) output += "\n";
    }
    return output;
}
