#ifndef SINGLETONBD_H
#define SINGLETONBD_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>



class singletonBD;//объявляемЮ что где-то есть класс


/**
 * @brief The singletonDest class
 */

class singletonDest//класс для очистки
{
private:
    /**
     * @brief p_instan создаем ссылку на объект singletonBD
     */
    singletonBD * p_instan;//создаем ссылку на объект singletonBD
public:
    /**
     * @brief ~singletonDest деструктор
     */
    ~singletonDest();

    /**
     * @brief initial просто копирует ссылки из singletonBD в singletonDest
     * @param p - ссылка
     */
    void initial(singletonBD * p);//просто копирует ссылки из singletonBD в singletonDest
};

/**
 * @brief The singletonBD class
 * @param p_instan ссылка на объект singletonBD
 * @param dest если вызывать singletonDest, он удалит все, что по ссылке (нужен отдельно деструктор, чтобы не сработал деструктор при вызове класса)
 * @param db сама бд
 */
class singletonBD
{
private:
    static singletonBD * p_instan; //ссылка на объект singletonBD
    static singletonDest dest; //если вызывать singletonDest, он удалит все, что по ссылке (нужен отдельно деструктор, чтобы не сработал деструктор при вызове класса)
    QSqlDatabase db; // сама бд

protected:
    /**
     * @brief singletonBD конструтор базы данных
     */
    singletonBD();
    singletonBD(const singletonBD&) = delete;
    singletonBD& operator = (singletonBD&) = delete;
    /**
     * @brief ~singletonBD деструктор базы данных для уаления объекта сервера и чистки памяти
     */
    ~singletonBD();
    friend class singletonDest;

public:
    /**
     * @brief getInstance медот получения единственного экземляра singletonBD
     * @return возвращает указатель на базу данных не создавая новые
     */
    static singletonBD * getInstance();//медот получения единственного экземляра singletonBD
    /**
     * @brief getValue метод для отправки в бд запросов
     * @return вохвразает ответ БД
     */
    QStringList getValue(QString);//метод для отправки в бд запросов
};


#endif // SINGLETONBD_H
