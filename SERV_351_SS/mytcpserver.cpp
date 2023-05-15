#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include "function.h"
MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,this,&MyTcpServer::slotNewConnection);
    if(!mTcpServer->listen(QHostAddress::Any,33333))
    {
       qDebug() << "Dead";
    }
    else
    {
        server_status=1;
        qDebug()<<"Not dead";
    }
}

void MyTcpServer::slotNewConnection()
{
    if(server_status==1)
    {
        QTcpSocket * curr_Socket;
        curr_Socket = mTcpServer->nextPendingConnection();

        connect(curr_Socket,&QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);

        connect(curr_Socket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);

        mTcpSocket.push_back(curr_Socket);
        qDebug()<<"slot creat";
    }
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *curr_Socket = (QTcpSocket*)sender();
    QString bufer;
    QByteArray arr;
    int fl=0;
    while(curr_Socket->bytesAvailable()>0)
    {
        arr = curr_Socket->readAll();
        bufer.append(arr);
        qDebug()<<"Запись";
    }

    arr.clear();
    bufer = bufer.left(bufer.indexOf('\r'));
    for(int i = 0; i<mTcpSocket.count();i++)
    {
        if(curr_Socket == mTcpSocket.at(i)) break;

        fl++;
    }
    curr_Socket->write(parse(bufer,fl));
    bufer.clear();
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *curr_Socket = (QTcpSocket*)sender();
    for(int i = 0; i<mTcpSocket.count();i++)
    {
        if(curr_Socket == mTcpSocket.at(i))
        {
            mTcpSocket.removeAt(i);
            qDebug()<<"slot delete";
            break;
        }
    }
}

