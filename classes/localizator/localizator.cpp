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
         QXmlStreamReader::TokenType token =  reader.readNext();
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
    return map[name];
}

void Localizator::localize(Ui::SNF_gui* ui)
{
   ui->label_2->setText(getTranslation("InputLabel"));
   ui->label->setText(getTranslation("OutputLabel"));
   ui->minimizeButton->setText(getTranslation("MinimizeButton"));
   ui->stepsButton->setText(getTranslation("StepsButton"));
   ui->conditionLabel->setText(getTranslation("ConditionDefault"));
}
