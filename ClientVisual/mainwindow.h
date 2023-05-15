#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "regauth.h"
#include "taskform.h"
#include "fun.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    regauth *ui_auth;
    TaskForm *ui_task;
    /**
     * @brief go_task функция для перехода между окнами (главным к задачаам)
     * @param task_num номер задачи
     */
    void go_task(QString task_num);
    /**
     * @brief check_point функция для установки количества баллов за задания
     * @param task номер задание
     * @return возвращает количество баллов за задание
     */
    QString check_point(QString task);
signals:
    /**
     * @brief go сигнал для октрытия окна task
     */
    void go(QString, QString);
private slots:
    /**
     * @brief slot_on_auth_closed сигнал на закрытие окн regauth и task
     */
    void slot_on_auth_closed(QString);
    /**
     * @brief on_Exit_button_clicked сигнал нажатие на кнопку для закрытия
     */
    void on_Exit_button_clicked();
    /**
     * @brief on_Task1_Button_clicked сигнал нажатие на кнопку task1 и дальнейший переход к taskform
     */
    void on_Task1_Button_clicked();
    /**
     * @brief on_Task2_Button_clicked сигнал нажатие на кнопку task2 и дальнейший переход к taskform
     */
    void on_Task2_Button_clicked();
    /**
     * @brief on_Task3_Button_clicked сигнал нажатие на кнопку task3 и дальнейший переход к taskform
     */
    void on_Task3_Button_clicked();
};
#endif // MAINWINDOW_H
