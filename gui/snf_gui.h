/**
  \file
  */
#ifndef SNF_GUI_H
#define SNF_GUI_H

#include <QWidget>
#include <QMenuBar>
#include "ui_snf_gui.h"
#include "classes/snf_minimizer/snf_minimizer.h"
#include "classes/localizator/localizator.h"

#include <QTime>

#include "log.h"
#include "help.h"


namespace Ui {
class SNF_gui;
}

/**
 * @brief SNF_gui
 */
class SNF_gui : public QWidget
{
    Q_OBJECT
    friend class Localizator;

public:
    /**
     * @brief SNF_gui
     * @param parent
     */
    explicit SNF_gui(QWidget *parent = 0);
    /**
      @brief ~SNF_gui
      */
    ~SNF_gui();

private slots:
    /**
     * @brief on_minimizeButton_clicked
     */
    void on_minimizeButton_clicked();

    /**
     * @brief langEn_clicked
     */
    void langEn_clicked();
    /**
     * @brief langRu_clicked
     */
    void langRu_clicked();
    /**
     * @brief help_clicked
     */
    void help_clicked();

    /**
     * @brief on_stepsButton_clicked
     */
    void on_stepsButton_clicked();

    /**
     * @brief sleep
     * @param ms
     */
    void sleep (unsigned int ms);

private:
    Ui::SNF_gui *ui;
    QString log;
    bool logShown = false;
    /**
     * @brief setLocale
     * @param locale
     */
    void setLocale (QString locale);
    /**
     * @brief createMenubar
     */
    void createMenubar();
    /**
     * @brief createLangMenu
     * @param bar
     */
    void createLangMenu(QMenuBar* bar);
    /**
     * @brief createHelpMenu
     * @param bar
     */
    void createHelpMenu(QMenuBar* bar);
};

#endif // SNF_GUI_H
