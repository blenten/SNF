#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "gui/snf_gui.h"
#include "gui/log.h"

class SNF_gui;
class Log;

//singleton class for translating texts, states and errors
class Localizator
{
private:
   QMap <QString, QString> map;
   Localizator(){}
   ~Localizator(){}
   Localizator (const Localizator &){}
   Localizator& operator=(const Localizator&);

public:
   void loadLocale(QString locale);

   //windows localization
   void localize(SNF_gui* window);
   void localize (Log* window);

   //will find translation for text by its name. Name must begin by '%' symbol
   QString getTranslation (QString name);

   QString translateLog(const QString &l);

   //singleton
   static Localizator& instance()
   {
       static Localizator l;
       return l;
   }
};

#endif // LOCALIZATOR_H
