#include "weather.h"
#include "ui_weather.h"

//JSON解析头文件hsuHj
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

weather::weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weather)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply_finished(QNetworkReply*)));//关联信号和槽


    QImage pixmap = QImage(":/new/image/weather.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

weather::~weather()
{
    delete ui;//
}

void weather::on_bt_search_clicked()
{
    QString local_city = ui->le_city->text().trimmed(); //获得需要查询天气的城市名称
    char quest_array[256]="http://wthrcdn.etouch.cn/weather_mini?city=";
    QNetworkRequest quest;
    //quest_array = quest_array + local_city.toUtf8().data();
    sprintf(quest_array,"%s%s",quest_array,local_city.toUtf8().data());
    quest.setUrl(QUrl(quest_array));
    quest.setHeader(QNetworkRequest::UserAgentHeader,"RT-Thread ART");
    /*发送get网络请求*/
    manager->get(quest);
}

void weather::on_bt_exit_clicked()
{
    emit weatherSignal();
}

void weather::reply_finished(QNetworkReply *reply)  //天气数据处理槽函数
{
    QString low;
    QString high;
    QString strength;
    QString data;
    QJsonValue value;
    QJsonObject today_weather;
    //qDebug()<<"recv weather data!!";
    QString all = reply->readAll();
    //ui->te_info->setText(all); //将接收到的数据显示出来

    QJsonParseError err;
    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(),&err);//解析json对象
//    //qDebug() << err.error;
    if(!json_recv.isNull())
    {
        QJsonObject object = json_recv.object();

        if(object.contains("data"))
        {
            value = object.value("data");  // 获取指定 key 对应的 value
            if(value.isObject())
            {
                QJsonObject object_data = value.toObject();
                ui->tb_tips->setText(object_data.value("ganmao").toString());
                ui->lb_city->setText(object_data.value("city").toString());
                ui->lb_tem_now->setText(object_data.value("wendu").toString());

                if(object_data.contains("yesterday"))
                {
                    value = object_data.value("yesterday");
                    if(value.isObject())
                    {
                        today_weather = value.toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fl").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fx").toString() + strength;
                        ui->lb_type_0->setText(weather_type); //显示天气类型
                        ui->lb_tem_0->setText(tem);   //显示温度
                        ui->lb_wind_0->setText(wind_dir); //显示风力
                        ui->lb_data_0->setText(data); //显示风力
                    }
                }

                if(object_data.contains("forecast"))
                {
                    value = object_data.value("forecast");
                    if(value.isArray())
                    {
                        today_weather = value.toArray().at(0).toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fengli").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fengxiang").toString() + strength;
                        ui->lb_weather_type->setText(weather_type); //显示天气类型
                        ui->lb_tem->setText(tem);   //显示温度
                        ui->lb_wind_dir->setText(wind_dir); //显示风力
                        ui->lb_data->setText(data); //显示风力

                        today_weather = value.toArray().at(1).toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fengli").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fengxiang").toString() + strength;
                        ui->lb_type_1->setText(weather_type); //显示天气类型
                        ui->lb_tem_1->setText(tem);   //显示温度
                        ui->lb_wind_1->setText(wind_dir); //显示风力
                        ui->lb_data_1->setText(data); //显示风力

                        today_weather = value.toArray().at(2).toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fengli").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fengxiang").toString() + strength;
                        ui->lb_type_2->setText(weather_type); //显示天气类型
                        ui->lb_tem_2->setText(tem);   //显示温度
                        ui->lb_wind_2->setText(wind_dir); //显示风力
                        ui->lb_data_2->setText(data); //显示风力

                        today_weather = value.toArray().at(3).toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fengli").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fengxiang").toString() + strength;
                        ui->lb_type_3->setText(weather_type); //显示天气类型
                        ui->lb_tem_3->setText(tem);   //显示温度
                        ui->lb_wind_3->setText(wind_dir); //显示风力
                        ui->lb_data_3->setText(data); //显示风力

                        today_weather = value.toArray().at(4).toObject();
                        weather_type = today_weather.value("type").toString();
                        data = today_weather.value("date").toString();
                        low = today_weather.value("low").toString();
                        high = today_weather.value("high").toString();
                        tem = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
                        strength = today_weather.value("fengli").toString();
                        strength.remove(0,8);
                        strength.remove(strength.length()-2,2);
                        wind_dir = today_weather.value("fengxiang").toString() + strength;
                        ui->lb_type_4->setText(weather_type); //显示天气类型
                        ui->lb_tem_4->setText(tem);   //显示温度
                        ui->lb_wind_4->setText(wind_dir); //显示风力
                        ui->lb_data_4->setText(data); //显示风力

                    }
                }
            }
        }

    }else
    {
        //qDebug()<<"json_recv is NULL or is not a object !!";
    }
    reply->deleteLater(); //销毁请求对象
}

