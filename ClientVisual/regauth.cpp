#include "regauth.h"
#include "ui_regauth.h"

regauth::regauth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regauth)
{
    ui->setupUi(this);
    this->swap_mode(true);
}

void regauth::swap_mode(bool m)
{
    ui->label_3->setVisible(!m);
    ui->lineEdit_mail->setVisible(!m);
    ui->Reg_Button->setVisible(!m);

    ui->Auth_Button->setVisible(m);
    if(m)
    {
        ui->Swap_Button->setText("To sing up");
    }
    else
    {
        ui->Swap_Button->setText("Cansel");
    }
}

regauth::~regauth()
{
    delete ui;
}

void regauth::on_Swap_Button_clicked()
{
    this->swap_mode(ui->label_3->isVisible());
    ui->lineEdit_log->clear();
    ui->lineEdit_pass->clear();
    ui->lineEdit_mail->clear();
}


void regauth::on_Reg_Button_clicked()
{

    ans = client->SendToServer("reg "+ ui->lineEdit_log->text() +" "+ ui->lineEdit_pass->text()+ " " + ui->lineEdit_mail->text());

    if(ui->lineEdit_log->text().isEmpty() || ui->lineEdit_pass->text().isEmpty() || ui->lineEdit_mail->text().isEmpty()){
       QMessageBox::critical(this,"Ошибка","Не заполнены или логин, или пароль, или мейл");
    }
    else if(ans == "reg&+"){
        QMessageBox::information(this,"Регистрация","Успех");
        ui->lineEdit_mail->clear();
        on_Swap_Button_clicked();
    }
    else if(ans =="reg&-"){
        QMessageBox::critical(this,"Ошибка","Такой логин или пароль заняты");
    }

}

void regauth::on_Auth_Button_clicked()
{


    ans = client->SendToServer("auth " + ui->lineEdit_log->text() + " " +ui->lineEdit_pass->text());
    if(ui->lineEdit_log->text().isEmpty() || (ui->lineEdit_pass->text().isEmpty())){
           QMessageBox::critical(this,"Ошибка","Не заполнены или логин, или пароль");
    }
    else if(ans == "auth&+"){//тут будет запрос на авторизацию
        qDebug() << "auth " + ui->lineEdit_log->text()+" "+ ui->lineEdit_pass->text();
        login = ui->lineEdit_log->text();
        //сюда сделаем фукнцию проверки есть ли такой пользователь и если она равна true мы ее
        emit closed(ui->lineEdit_log->text());
        this->close();
    }
    else if(ans == "auth&-"){
            QMessageBox::critical(this,"Ошибка","Неправильный или логин или пароль");
    }

}

