#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "gui/snf_gui.h"
#include "gui/log.h"
#include "gui/help.h"

class SNF_gui;
class Log;
class Help;

//singleton class for translating texts, states and errors
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

   //windows localization
   void localize(SNF_gui* window);
   void localize (Log* window);
   void localize (Help* window);

   //returns translation of string by name and inserts args in output string. Name must start with '%'
   QString translate (QString name, std::vector<QString> args);
   QString translate (QString name);

   QString translateLog(const QString &l);

   //singleton
   static Localizator& instance()
   {
       static Localizator l;
       return l;
   }
};

#endif // LOCALIZATOR_H
