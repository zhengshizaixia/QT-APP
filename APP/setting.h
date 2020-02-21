#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_bt_set_clicked();

    void on_bt_select_clicked();

private:
    Ui::setting *ui;

signals:
    void settingSignal(QString);
};

#endif // SETTING_H
