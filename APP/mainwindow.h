#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setting.h"
#include "led.h"
#include "weather.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setting_clicked();
    void setting_to_mainwindow(QString path);
    void led_to_mainwindow();
    void weather_to_mainwindow();

    void on_led_clicked();
    void on_weather_clicked();

private:
    Ui::MainWindow *ui;
    setting *forms_setting;
    led *forms_led;
    weather *forms_weather;

};
#endif // MAINWINDOW_H
