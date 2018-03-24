#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "../snfg.h"
#include "..//log.h"
#include "../help.h"

class SNFG;
class Log;
class Help;

class Localizator
{
private:
   QJsonObject localeJson;

   Localizator(){}
   ~Localizator(){}
   Localizator (const Localizator &){}
   Localizator& operator=(const Localizator&);

   QString insertArgsIntoString(QString str, std::vector<QString> &args);

public:

   void loadLocale(QString locale);

   void localize(SNFG* window);

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
