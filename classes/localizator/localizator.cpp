#include "../localizator/localizator.h"

void Localizator::loadLocale()
{
    QFile file(":locale/locale_ru_RU.xml");
    file.open(QIODevice::ReadOnly);
    QByteArray byte=file.readAll();
    file.close();

    QXmlStreamReader reader;
    reader.addData(byte);
    while (!reader.atEnd() && !reader.hasError())
    {
         QXmlStreamReader::TokenType token =  reader.readNext();
         if (token == QXmlStreamReader::StartDocument) continue;

         if (reader.name()=="Main" || reader.name()=="Exception") continue;

       if (reader.text().toString().trimmed()!="") (reader.text().toString());
    }
}
