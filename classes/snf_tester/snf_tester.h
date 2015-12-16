/**
  \file
*/

#ifndef SNF_TESTER_H
#define SNF_TESTER_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <QElapsedTimer>
#include <QObject>

/**
 * @brief SNF_Tester
 *
 * Производит тестирование производительности алгоритма минимизации
 */
class SNF_Tester: public QObject
{    
    Q_OBJECT

private:
    std::ofstream logStream; ///< поток вывода прогресса выполнения

    double stepsCount; ///<число шагов тестирования
    bool isStopped; ///<флаг остановки потока

    std::vector<std::string> generatedOperands;
    std::vector <quint64> maxOperandsNumbers; //max numbers of operands for each variables number to avoid repeating (equals 2 to the number power)

    /**
     * @brief checkRanges
     *
     * Проверяет введенные данные во избежание переполнения
     * @return
     */
    bool checkRanges();

    /**
     * @brief getMaxOperandsNumbers
     *
     *Рассчитывает максимальное количество неповторяющихся операндов для каждого числа переменных
     */
    void getMaxOperandsNumbers();

    /**
     * @brief getStepsCount
     *
     * Рассчитывает количество шагов, в которые будет проведен тест
     */
    void getStepsCount();

    /**
     * @brief testMinimizing
     *
     * Запускает тестирование
     */
    void testMinimizing();

    /**
     * @brief getRandom
     *
     * Обертка над функцией rand()
     * @param max - максимальное число
     * @return
     */
    int getRandom (int max);

    /**
     * @brief getMinimizingTime
     *
     * Получает время минимизации функции
     * @param function
     * @return
     */
    double getMinimizingTime (std::string function);

    /**
     * @brief minimize
     *
     * Обертка над классом Minimizer
     * @param function
     * @return
     */
    std::string minimize (std::string function);

    /**
     * @brief logHead
     *
     * Вывод шапки лога
     */
    void logHead();

    /**
     * @brief logCurrentFunction
     *
     * Логирование данных о минимизации функции
     * @param currentVariablesNumber - число переменных в функции
     * @param currentOperandsNumber - число операндов в функции
     * @param currentTime - время минимизации
     */
    void logCurrentFunction (int currentVariablesNumber, int currentOperandsNumber, double currentTime);

    /**
     * @brief logInfoPercentCompleted
     *
     * Вывод процента выполнения тестирования
     * @param percent
     */
    void logInfoPercentCompleted(double percent);

    /**
     * @brief generateOperand
     *
     * Генерирует случайный операнд
     * @param variablesNumber - число переменных
     * @param ft - тип функции
     * @return
     */
    std::string generateOperand(quint64 variablesNumber, FunctionType ft);

    /**
     * @brief isOperandRepeated
     *
     * Проверка операнда на дублирование
     * @param operand - проверяемый операнд
     * @return
     */
    bool isOperandRepeated (std::string operand);

public:
    unsigned int downVariablesNumber; ///<нижний предел числа переменных
    unsigned int upVariablesNumber; ///< верхний предел числа переменных
    unsigned int variablesStep; ///< шаг изменения
    unsigned int downOperandsNumber; ///<нижний предел числа операндов
    unsigned int upOperandsNumber; ///< верхний предел числа операндов
    unsigned int operandsStep; ///< шаг изменения
    std::string logPath; ///< путь создания файла лога

    /**
     * @brief generateFunction
     *
     * Генерирует случайную функцию
     * @param variablesNumber - число переменных
     * @param operandsNumber - число операндов
     * @param ft - тип функции
     * @return
     */
    std::string generateFunction (quint64 variablesNumber, quint64 operandsNumber, FunctionType ft);

signals:
    /**
     * @brief onInfoSend
     *
     * Подает сигнал с информацией
     * @param info
     */
    void onInfoSend(QString info);

    /**
     * @brief finish
     *
     * Сигнализирует о завершении
     */
    void finish();

public slots:

    /**
     * @brief start
     *
     * Старт потока тестирования
     */
    void start();

    /**
     * @brief stop
     *
     * Завершение потока
     */
    void stop();
};

#endif
