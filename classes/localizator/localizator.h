/**
  \file
  */

#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <qxmlstream.h>
#include <QFile>
#include <QByteArray>
#include <QMap>

#include "gui/snf_gui.h"
#include "gui/log.h"
#include "gui/help.h"

class SNF_gui; ///<Главное окно
class Log; ///< Окно лога
class Help; ///< Окно справки

/**
 * @brief Localizator
 *
 * Синглтон для перевода текстов, состояний и ошибок
 */
class Localizator
{
private:
   QMap <QString, QString> map; ///<Содержит строки, ищущиеся по их кодовым именам

   /**
    * @brief Localizator
    *
    * Закрытый конструктор
    */
   Localizator(){}

   /**
    * @brief ~Localizator
    *
    * Закрытый деструктор
    */
   ~Localizator(){}

   /**
    * @brief Localizator
    *
    * Закрытый конструктор копирования
    */
   Localizator (const Localizator &){}

   /**
    * @brief operator =
    *
    * Закрытый оператор присваивания
    * @return
    */
   Localizator& operator=(const Localizator&);

   /**
    * @brief insertArgsIntoString
    *
    * Осуществляет подстановку аргументов в строку
    * @param str - кодовое имя строки
    * @param args - подставляемые аргументы
    * @return Результирующая строка
    */
   QString insertArgsIntoString(QString str, std::vector<QString> &args);

public:
   /**
    * @brief loadLocale
    *
    * Осуществляет считывание файла локали в локализатор, если таковая локаль имеется.
    * @param locale - имя локали
    */
   void loadLocale(QString locale);

   /**
    * @brief localize
    *
    * Осуществляет перевод главного окна
    * @param window - окно , которое будет локализовано
    */
   void localize(SNF_gui* window);

   /**
    * @brief localize
    *
    * Осуществляет перевод главного окна
    * @param window - окно , которое будет локализовано
    */
   void localize (Log* window);

   /**
    * @brief localize
    *
    * Осуществляет перевод главного окна
    * @param window - окно , которое будет локализовано
    */
   void localize (Help* window);

   /**
    * @brief translate
    *
    * Переводит строку, подставляя аргументы
    * @param name - кодовое имя строки для перевода
    * @param args - аргументы для подстановки
    * @return Переведенная строка
    */
   QString translate (QString name, std::vector<QString> args);

   /**
    * @brief translate
    *
    * Переводит строку без подстановки аргументов
    * @param name - кодовое имя строки для перевода
    * @return Переведенная строка
    */
   QString translate (QString name);

   /**
    * @brief translateLog
    *
    * Переводит лог
    * @param l - строка лога
    * @return
    */
   QString translateLog(const QString &l);

   /**
    * @brief instance
    *
    * Инстанс локализатора
    * @return Объект класса
    */
   static Localizator& instance()
   {
       static Localizator l;
       return l;
   }
};

#endif // LOCALIZATOR_H
