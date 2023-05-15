#ifndef REGAUTH_H
#define REGAUTH_H
#include <QWidget>
#include <QMessageBox>
#include <QString>
#include "fun.h"
namespace Ui {
class regauth;
}

class regauth : public QWidget
{
    Q_OBJECT

public:
    explicit regauth(QWidget *parent = nullptr);
    ~regauth();
private slots:
    /**
     * @brief on_Swap_Button_clicked сигнал нажатие на кнопку перехода на регистрацию
     */
    void on_Swap_Button_clicked();
    /**
     * @brief on_Reg_Button_clicked сигнал нажатие на кнопку регистрация пользователя и дальшейшую проврерку на регистрацию
     */
    void on_Reg_Button_clicked();
    /**
     * @brief on_Auth_Button_clicked сигнал нажатие на кнопку авторизацию пользователя и дальшейшую проврерку на авторизацию
     */
    void on_Auth_Button_clicked();

private:
    Ui::regauth *ui;
    /**
     * @brief swap_mode функция для смены между режимами регистрации и авторизации
     */
    void swap_mode(bool);
    /**
     * @brief ans ответ от сервера
     */
    QString ans;
signals:
    /**
     * @brief closed сигнла на закрытия этого окна
     * @param login логин пользователя
     */
    void closed(QString login);
};

#endif // REGAUTH_H
