#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "snf_gui.h"
#include "log.h"

//singleton class for translating texts, states and errors
class Localizator
{
private:
   QMap <QString, QString> map;
   Localizator(){}
   ~Localizator(){}
   Localizator (const Localizator &){}
   Localizator& operator=(const Localizator&){}

public:

   void loadLocale(QString locale);

   //will find translation for text by its name. Name must begin by '%' symbol
   QString getTranslation (QString name);

   //main window localization ()
   void localize (Ui::SNF_gui* ui);

   //singleton
   static Localizator& instance()
   {
       static Localizator l;
       return l;
   }
};

#endif // LOCALIZATOR_H
