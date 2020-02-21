#include "weather.h"
#include "ui_weather.h"

//JSON解析头文件
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
}

weather::~weather()
{
    delete ui;
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
    //qDebug()<<"recv weather data!!";
    QString all = reply->readAll();
    ui->te_info->setText(all); //将接收到的数据显示出来

//    QJsonParseError err;
//    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(),&err);//解析json对象
//    //qDebug() << err.error;
//    if(!json_recv.isNull())
//    {
//        QJsonObject object = json_recv.object();

//        if(object.contains("data"))
//        {
//            QJsonValue value = object.value("data");  // 获取指定 key 对应的 value
//            if(value.isObject())
//            {
//                QJsonObject object_data = value.toObject();
//                if(object_data.contains("forecast"))
//                {
//                    QJsonValue value = object_data.value("forecast");
//                    if(value.isArray())
//                    {
//                        QJsonObject today_weather = value.toArray().at(0).toObject();
//                        weather_type = today_weather.value("type").toString();

//                        QString low = today_weather.value("low").toString();
//                        QString high = today_weather.value("high").toString();
//                        wendu = low.mid(low.length()-3,4) +"~"+ high.mid(high.length()-3,4);
//                        QString strength = today_weather.value("fengli").toString();
//                        strength.remove(0,8);
//                        strength.remove(strength.length()-2,2);
//                        fengli = today_weather.value("fengxiang").toString() + strength;
//                        ui->type->setText(weather_type); //显示天气类型
//                        ui->wendu->setText(wendu);   //显示温度
//                        ui->fengli->setText(fengli); //显示风力
//                    }
//                }
//            }
//        }

//    }else
//    {
//        qDebug()<<"json_recv is NULL or is not a object !!";
//    }
    reply->deleteLater(); //销毁请求对象
}

