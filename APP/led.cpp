#include "led.h"
#include "ui_led.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

led::led(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::led)
{
    ui->setupUi(this);
}

led::~led()
{
    delete ui;
}

void led::on_bt_exit_clicked()
{
    emit ledSignal();
}

void led::on_bt_close_clicked()
{
    int fd = 0;
    int userdata = 0;
    fd = open("/dev/led_platform_dts_dev",O_RDWR);
    write(fd, &userdata, sizeof(userdata));
    //close(fd)
}

void led::on_bt_open_clicked()
{
    int fd = 0;
    int userdata = 1;
    fd = open("/dev/led_platform_dts_dev",O_RDWR);
    write(fd, &userdata, sizeof(userdata));
    //close(fd);
}
