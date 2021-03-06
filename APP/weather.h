#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QMainWindow>
namespace Ui {
class weather;
}

class weather : public QWidget
{
    Q_OBJECT

public:
    explicit weather(QWidget *parent = nullptr);
    ~weather();

private slots:
    void on_bt_search_clicked();

    void on_bt_exit_clicked();

    void reply_finished(QNetworkReply *reply);

private:
    Ui::weather *ui;
    QNetworkAccessManager *manager;

    QString wind_dir;       //风力
    QString tem;        //温度
    QString weather_type;  //天气类型
signals:
    void weatherSignal();
    void finished(QNetworkReply*);
};

#endif // WEATHER_H
