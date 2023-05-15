#ifndef SINCLIENT_H
#define SINCLIENT_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtNetwork>
#include <QObject>
#include <QDebug>


class sinclient;//объявляем что где-то есть класс

class sinclientdest
{
private:
    sinclient * p_instance;//ссыкла на sinclient
public:
    ~sinclientdest ();
    void initialize(sinclient * p);//просто копирует ссылки из sinclient в sinclientdest
};

class sinclient : public QObject // сам класс sinclient плюс наследование
{
private:
    QTcpSocket * Socket;//Делаем указатель на SOcket
    static sinclient * p_instance;//указатель на объект этого класса
    static sinclientdest destroyer; //если вызывать SingClientDestroyer, он удалит все, что по ссылке (нужен отдельно деструктор, чтобы не сработал деструктор при вызове класса)
    QString answer;
protected:
    sinclient();//кострутор

    sinclient(const sinclient& ) = delete;
    sinclient& operator = (sinclient &) = delete;

    ~sinclient(); //Здесь пишем socket close()
    friend class sinclientdest;
public:
    /**
     * @brief SendToServer функция для отправка на сервер запроса
     * @param temp сам запрос
     * @return возвращает ответ
     */
    QString SendToServer(QString temp) const;
    /**
     * @brief getInstance как раз за счет этого и работает паттерн Singleton
     * @return возвращает единственный объект клиента не создавая нового и тем самым не забиваает память
     */
    static sinclient* getInstance();//как раз за счет этого и работает паттерн Singleton
protected slots:
    /**
     * @brief slotReadyRead чтение данных из активного сокета
     */
    void slotReadyRead();//слот для чтения данных из сокета
    /**
     * @brief slotClientDisconnected функция отключения клиента от сервера
     */
    void slotClientDisconnected();//слот для обработки отключения от сервера
signals:

};

#endif // SINCLIENT_H
