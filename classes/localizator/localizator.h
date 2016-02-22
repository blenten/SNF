#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "gui/log.h"
#include "gui/help.h"

//la changing gui class costille
#include "gui/snfg.h"
#define GUICLASS SNFG

class GUICLASS;
class Log;
class Help;

class Localizator
{
private:
   QMap <QString, QString> map;

   Localizator(){}
   ~Localizator(){}
   Localizator (const Localizator &){}
   Localizator& operator=(const Localizator&);

   QString insertArgsIntoString(QString str, std::vector<QString> &args);

public:

   void loadLocale(QString locale);

   void localize(GUICLASS* window);

   void localize (Log* window);

   void localize (Help* window);

   QString translate (QString name, std::vector<QString> args);

   QString translate (QString name);

   QString translateLog(const QString &l);

   static Localizator& instance()
   {
       static Localizator l;
       return l;
   }
};

#endif // LOCALIZATOR_H
