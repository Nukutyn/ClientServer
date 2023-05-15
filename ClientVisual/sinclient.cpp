#include "sinclient.h"
#include "fun.h"
sinclient * sinclient::p_instance;
sinclientdest sinclient::destroyer;


sinclientdest::~sinclientdest()
{
    delete p_instance;//удаляем указатель
}
void sinclientdest::initialize(sinclient * p)
{
    p_instance = p;//копируем
}
sinclient::sinclient()
{
        Socket = new QTcpSocket;//выделяем память под сокет
        Socket->connectToHost("127.0.0.1",33333);//коннектимся к хосту

        connect(Socket,&QTcpSocket::readyRead,
                this,&sinclient::slotReadyRead);//уставновление соединение между readyRead и slotReadyRead

        connect(Socket,&QTcpSocket::disconnected,
                this,&sinclient::slotClientDisconnected);//уставновление соединение между disconnected и slotClientDisconnected

} //Здеась пишем подключение к серверу и connect signal slot

sinclient::~sinclient()
{
    Socket->close();//загрываем сокет
    delete Socket;//чистим память
}
sinclient* sinclient::getInstance()
{
    p_instance = new sinclient(); //выделяем память под ссылку
    destroyer.initialize(p_instance); //тут ссылка в дестроере совпадает с ссылкой в синглтоне
    return p_instance;//возвращаем указатель
}

void sinclient::slotReadyRead()
{
    QByteArray array;//нужно для сычитывания с косоли
    QString mes;//нужно чтобы инфа из консоли добалялась сюда
    while(Socket->bytesAvailable()>0)//сама логика считывания
    {
        array = Socket->readAll();
        mes.append(array);
    }
    array.clear();//чистим
    qDebug()<<mes;//выводим
    answer = mes;
}
void sinclient::slotClientDisconnected()
{
    Socket->close();//закрываем сокет
    delete Socket;
}


QString sinclient::SendToServer(QString temp) const
{
    try {
        Socket->write(temp.toUtf8());

        Socket->waitForReadyRead();
        return answer;
    } catch (const std::exception & e)
    {
        return "Error";
    }
}
