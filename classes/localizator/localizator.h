#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

class Localizator
{
private:


public:
   void loadLocale(QString locale);
   QMap <QString, QString> map;
};

#endif // LOCALIZATOR_H
