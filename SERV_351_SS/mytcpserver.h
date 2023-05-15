#ifndef MYTCPSERVER_H //аналог pragma once
#define MYTCPSERVER_H


#include <QObject>
#include <QTcpServer> ///tcp сервер (прослушивание канала, сигнал о подключении - все, что уже готово)
#include <QTcpSocket>

//в cpp пишем все include
#include <QtNetwork> //указание порта, хоста
#include <QByteArray> //передаются биты
#include <QDebug> //вывод в консоль

#include <QVector>
#include <algorithm>
#include <QCoreApplication>

/**
 * @brief The MyTcpServer class класс сервер для установления соединения и выполнения задач
 * @param mTcpServer переменная отвечащая за состояния сервера
 * @param mTcpSocket вектор со всеми подключениями
 * @param server_status индикатор сервера
 * @param fl флаг для обхода ошибок связанных с выводом
 */
class MyTcpServer : public QObject
{
    Q_OBJECT //где-то в аду есть define, по которому понятно, что это такое, и с чем это едят
public:
//explicit - командное слово, которое говорит что конструктор
//не приемлет неявное преобразование типов
//распростараняется на всю функцию, а не только ее параметры
//по аналогии с const

//в нашем проекте можно без expicit
    /**
     * @brief MyTcpServer Инициализация нового экземпляра сервера
     * @param parent параметр нужный для инициализации базового класса
     */
    explicit MyTcpServer(QObject *parent = nullptr); //конструктор
    /**
     * @brief MyTcpServer уничтожает экземпляра сервера и чистит памяти
     */
    ~MyTcpServer(); //деструктор
public slots: //вызывается в случае срабатывания какого-либо сигнала

    /**
     * @brief slotNewConnection функция установки соединения с сервером
     */
    void slotNewConnection();

    /**
     * @brief slotClientDisconnected функция отключения от сурвера
     */
    void slotClientDisconnected();
    /**
     * @brief slotServerRead чтение данных из активного сокета
     */
    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    QVector<QTcpSocket *> mTcpSocket;
    int server_status;
};
#endif // MYTCPSERVER_H //аналог pragma once
