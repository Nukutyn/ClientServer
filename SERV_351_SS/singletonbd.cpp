#include "singletonbd.h"

singletonBD * singletonBD::p_instan;
singletonDest singletonBD::dest;

singletonBD::singletonBD()
{

    db = QSqlDatabase::addDatabase("QSQLITE");// подключаем к SQLITE
    db.setDatabaseName("./TestDB.db");
    if(db.open())
    {
        qDebug()<<"open";
    }
    else qDebug()<<"no open";
    QSqlQuery query(db);
    if (db.tables().contains(QLatin1String("User")))
    {
       qDebug()<<"Be";
    }
    else
    {
        query.exec("CREATE TABLE User (Login VARCHAR(20) NOT NULL UNIQUE, Password VARCHAR(20) NOT NULL, Mail VARCHAR(20) NOT NULL UNIQUE, task1 INT, task2 INT, task3 INT, task4 INT,Unique_Num VARCHAR(100) UNIQUE);");
        qDebug()<<"create";
    }

}
//QStringList singletonBD::getValue(QStringList log)

/* query.prepare(log[0]);
 log.pop_front();
 while(log.size()>0)
 {
     query.bindValue(log.front());
     log.pop_front();
 }
 query.exec();
*/
QStringList singletonBD::getValue(QString log)
{
    QSqlQuery query(db);
    QStringList res;
    if(query.exec(log))
    {
        int num_of_cols = query.record().count();

        while(query.next())
        {
            for(int i = 0; i<num_of_cols;i++)
            {
                res.append(query.value(i).toString());//забираем столбецы
            }
        }

        qDebug()<<res;

        return res;
    }
    else
    {
        res.append("eror");
        return res;
    }
}

singletonBD::~singletonBD()
{
    if(p_instan!=nullptr)
    {
        db.close();//закрываем бд
    }
}

singletonDest::~singletonDest()
{
   delete p_instan;//удаляем указатель
}

void singletonDest::initial(singletonBD * p)
{
    p_instan = p;//просто копирует ссылки из singletonBD в singletonDest
}

singletonBD* singletonBD::getInstance()
{
    if (!p_instan)
    {
        p_instan = new singletonBD();//просто копирует ссылки из Singleton в SingletonDestroyer
        dest.initial(p_instan);//тут ссылка в дестроере совпадает с ссылкой в синглтоне
    }

    return p_instan;
}

