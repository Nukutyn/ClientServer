#ifndef TASKFORM_H
#define TASKFORM_H
#include "sinclient.h"
#include <QWidget>
#include <QDateTime>
#include <time.h>
#include <QMessageBox>
#include <QString>
#include "fun.h"

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = nullptr);
    ~TaskForm();

private slots:
    /**
     * @brief on_BackButton_clicked сигнал нажатие на кнопку back для возвращения на главный экран
     */
    void on_BackButton_clicked();
    /**
     * @brief on_EnterButton_clicked сигнал нажатие на кнопку enter для ввода ответа и отправки его на сервер
     */
    void on_EnterButton_clicked();

private:
    Ui::TaskForm *ui;
    QString rigt_ans;

    QStringList zadacha;
    QString ans;
    /**
     * @brief generatVar функция прикол для прикола
     */
    void generatVar(QString);
signals:
    /**
     * @brief back сингал на возвращение на окно главного экрана
     */
    void back(QString);
public slots:
    /**
     * @brief open сигнал на открытие этого окна с двумя параметрами task_num и log
     * @param task_num номер задачи
     * @param log логин пользователя
     */
    void open(QString task_num,QString log);
};

#endif // TASKFORM_H
