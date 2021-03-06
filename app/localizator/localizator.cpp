#include "localizator/localizator.h"

void Localizator::loadLocale(QString locale)
{
    QFile file(":locale/locale_" + locale + ".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString byte = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(byte.toUtf8());
    localeJson = document.object();
}

void Localizator::localize(SNFG *window)
{
    window->ui->inputLabel->setText(translate("%InputLabel"));
    window->ui->outputLabel->setText(translate("%OutputLabel"));
    window->ui->minimizeButton->setText(translate("%MinimizeButton"));
    window->ui->stepsButton->setText(translate("%StepsButton"));
    window->ui->conditionLabel->setText(translate("%ConditionDefault"));
    window->ui->menuMethod->setTitle(translate("%MethodMenu"));
    window->ui->menuMethod->actions().at(0)->setText(translate("%AlgebraicMethod"));
    window->ui->menuMethod->actions().at(1)->setText(translate("%QuineMethod"));

    window->ui->menuHelp->setTitle(translate("%HelpMenu"));
    window->ui->menuHelp->actions().at(0)->setText(translate("%UserGuideAction"));

    window->setWindowTitle(translate("%Title", {"2.0"}));
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
    return localeJson.value(name).toString();
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
