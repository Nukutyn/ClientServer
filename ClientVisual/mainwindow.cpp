#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_auth = new regauth;
    ui_task = new TaskForm;
    connect(ui_auth, &regauth::closed, this, &MainWindow::slot_on_auth_closed);
    connect(this,&MainWindow::go,ui_task,&TaskForm::open);
    connect(ui_task,&TaskForm::back, this, &MainWindow::slot_on_auth_closed);
    ui_auth->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::check_point(QString task)
{
    //тут функция запроса к бд на получение баллов за таски
    return client->SendToServer("point "+ task +" "+ ui->Label_login->text());
}

void MainWindow::slot_on_auth_closed(QString log)
{

    ui->Label_login->setText(log);
    //здесь вообще чтото сложное если вкратце мы считываем название lable он назван taskN,
    ui->Label_point1->setText(check_point(ui->Label_point1->text()));
    ui->Label_point2->setText(check_point(ui->Label_point2->text()));
    ui->Label_point3->setText(check_point(ui->Label_point3->text()));
    //N - это числа от 1 до 4 и кидаем запрос к БД на проврерку сколько баллов по этому task пользователь имеет и возвращаем число конвертируя его в QString

    this->show();
}


void MainWindow::on_Exit_button_clicked()
{

    this->close();
}


void MainWindow::go_task(QString task_num)
{
    ui->Label_point1->setText("task1");
    ui->Label_point2->setText("task2");
    ui->Label_point3->setText("task3");
    emit go(task_num,ui->Label_login->text());
    this->close();
}

void MainWindow::on_Task1_Button_clicked()
{
    go_task("task1");
}


void MainWindow::on_Task2_Button_clicked()
{
    go_task("task2");
}


void MainWindow::on_Task3_Button_clicked()
{
    go_task("task3");
}

