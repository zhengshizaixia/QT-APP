#ifndef LED_H
#define LED_H

#include <QWidget>

namespace Ui {
class led;
}

class led : public QWidget
{
    Q_OBJECT

public:
    explicit led(QWidget *parent = nullptr);
    ~led();

private slots:
    void on_bt_exit_clicked();

    void on_bt_close_clicked();

    void on_bt_open_clicked();

private:
    Ui::led *ui;
signals:
    void ledSignal();
};

#endif // LED_H
