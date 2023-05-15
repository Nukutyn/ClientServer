#ifndef FUNCTION_H
#define FUNCTION_H
#include <QByteArray>
#include <iostream>
#include <vector>
#include<queue>
#include<stack>
#include<string>
#include<random>
#include<time.h>
#include<iomanip>
#include<set>
#include "singletonbd.h"

/**
 * @brief parse функция парса
 * @param msg сообщение полученное сервером от пользователя обрабатывающиеся вв это фукнции
 * @return возвращает QByteArray с ответом
 */
QByteArray parse(QString msg,int position);

/**
 * @brief sign_in функция подключения
 * @param temp сообщение без приписки
 * @return возвращает или auth&+ или auth&- что означает что все хорошо или нет
 */
QString sign_in(QStringList temp);//фукция входа

/**
 * @brief sign_up функция регистрации
 * @param temp сообщение без приписки
 * @return возвращает или reg&+ или reg&- что означает что все хорошо или нет
 */
QString sign_up(QStringList temp);//функция регистрации

/**
 * @brief task_toBD после обработки сервером ответа заносит сюда или +1 или -1
 * @param temp сообщение без приписки
 */
void task_toBD(QStringList temp);//функции занесения в БД резултата task_1

/**
 * @brief get_tack функция выдачи задания
 * @param temp сообщение без приписки
 * @return возвращает задание и отправляет его на клиент
 */
QString get_tack(QStringList temp);//функция выдачи task

/**
 * @brief get_point функция для показания очков за задания
 * @param temp сообщение без приписки
 * @return возвращает количество очков за задание
 */
QString get_point(QStringList temp);




//void dis(QStringList temp);


//! жопа
bool try_kuhn(int v, std::vector<char>& used, std::vector<int>& mt, std::vector<std::vector<int>>& g);
void randvec(std::vector<std::vector<int>>& g, int n, int m);
bool dolgrap(QString answer);
void randvec(std::vector<std::vector<int>>& g, int n, int m);
int fun();





#endif // FUNCTION_H
