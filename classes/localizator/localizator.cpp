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
         {
            currName= reader.name().toString();
         }


         if (reader.text().toString().trimmed()!="")
         {
           //  std::cerr<<currName.toStdString()<<" " <<reader.text().toString().toStdString()<<"\n";
             map.insert(currName, reader.text().toString());
         }
    }

}
