#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);
}

TaskForm::~TaskForm()
{
    delete ui;
}


void TaskForm::generatVar(QString task_num)
{
    srand(time(NULL));
    if(task_num=="task1")
    {
        ui->VarNum->setText(QString::number(rand()%10000));
    }
    else if(task_num=="task2")
    {
        ui->VarNum->setText(QString::number(rand()%2312));
    }
    else if(task_num=="task3")
    {
        ui->VarNum->setText(QString::number(rand()%2300));
    }
}

void TaskForm::open(QString task_num,QString log)
{
    ui->NumTask->setText(task_num);
    ui->Login->setText(log);
    if(task_num=="task1")
    {
        ans = client->SendToServer("get "+task_num);

        zadacha = ans.split("||");
        rigt_ans = zadacha[1];
        ui->label_2->setText(zadacha[0]);
    }
    else if(task_num=="task2")
    {
        ans = client->SendToServer("get "+task_num);
        zadacha = ans.split("||");
        rigt_ans = zadacha[1];

        ui->label_2->setText(zadacha[0]);
    }
    else if(task_num=="task3")
    {

    }
    ui->lineEdit->setReadOnly(false);
    ui->EnterButton->setEnabled(true);
    generatVar(task_num);
    this->show();

}



void TaskForm::on_BackButton_clicked()
{
    QString log = ui->Login->text();
    emit back(log);
    ui->YourTask_2->setText("YourAnswer");
    ui->RightTask_3->setText("RightAnsewer");
    ui->label_2->setText("SAM TASK OPIC");
    ui->lineEdit->clear();
    this->close();
}


void TaskForm::on_EnterButton_clicked()
{
    if(ui->NumTask->text()=="task1")
    {
        if(ui->lineEdit->text().isEmpty()||ui->lineEdit->text().count(" ")==ui->lineEdit->text().size()){
            QMessageBox::critical(this,"Ошибка","EMPTY");
        }
        else{
            if(client->SendToServer("ans "+ rigt_ans + " " +ui->lineEdit->text()+ " " + ui->NumTask->text() + " -/+1 " + ui->Login->text())=="+1")
            {
                ui->RightTask_3->setText("Все верно " + rigt_ans);
            }
            else
            {
                ui->RightTask_3->setText("Лови -1 и вот ответ "+ rigt_ans);
            }



            ui->YourTask_2->setText(ui->lineEdit->text());

            ui->lineEdit->setReadOnly(true);
            ui->EnterButton->setEnabled(false);
            ui->lineEdit->clear();
        }
    }
    else if(ui->NumTask->text()=="task2")
    {
        if(ui->lineEdit->text().isEmpty()||ui->lineEdit->text().count(" ")==ui->lineEdit->text().size()){
            QMessageBox::critical(this,"Ошибка","EMPTY");
        }
        else
        {
            if(client->SendToServer("ans2 "+ ui->lineEdit->text()+" "+ rigt_ans + " "+ ui->NumTask->text() + " -/+1 " + ui->Login->text())=="+1"){
                ui->RightTask_3->setText("Все верно такие паросочетания существуют");
            }
            else{
                ui->RightTask_3->setText("Лови -1");
            }

            ui->YourTask_2->setText(ui->lineEdit->text());

            ui->lineEdit->setReadOnly(true);
            ui->EnterButton->setEnabled(false);
            ui->lineEdit->clear();
        }
    }


}

