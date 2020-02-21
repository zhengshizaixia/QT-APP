#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDir"
#include "QFileDialog"
#include "QTextCursor"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    forms_setting = new setting;
    QObject::connect(forms_setting,SIGNAL(settingSignal(QString)),this,SLOT(setting_to_mainwindow(QString)));

    forms_led = new led;
    QObject::connect(forms_led,SIGNAL(ledSignal()),this,SLOT(led_to_mainwindow()));

    forms_weather = new weather;
    QObject::connect(forms_weather,SIGNAL(weatherSignal()),this,SLOT(weather_to_mainwindow()));

    QImage pixmap = QImage(":/new/image/bg2.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
        delete ui;
}


void MainWindow::on_setting_clicked()
{
    forms_setting->show();
    this->hide();
}
void MainWindow::on_weather_clicked()
{
    forms_weather->show();
    this->hide();
}
void MainWindow::on_led_clicked()
{
    forms_led->show();
    this->hide();
}


void MainWindow::setting_to_mainwindow(QString path)
{
    forms_setting->hide();
    this->show();
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QImage(path)));
    this->setPalette(pal);
}
void MainWindow::led_to_mainwindow()
{
    forms_led->hide();
    this->show();
}

void MainWindow::weather_to_mainwindow()
{
    forms_weather->hide();
    this->show();
}


