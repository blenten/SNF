#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "snf_gui.h"
#include "log.h"

class Localizator
{
private:
   QMap <QString, QString> map;
   Localizator(){}
   ~Localizator(){}
   Localizator (const Localizator &);


public:

   void loadLocale(QString locale);

   QString getTranslation (QString name);

   void localize (Ui::SNF_gui* ui);

    static Localizator& instance()
    {
        static Localizator l;
        return l;
    }
};

#endif // LOCALIZATOR_H
