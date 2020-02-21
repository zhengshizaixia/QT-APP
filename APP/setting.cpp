#include "setting.h"
#include "ui_setting.h"
#include "QDir"
#include "QFileDialog"
#include "QTextCursor"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

void setting::on_bt_set_clicked()
{
    QString image_path;

    image_path = ui->lb_image_path->text();

    emit settingSignal(image_path);
}

void setting::on_bt_select_clicked()
{
    QStringList  path_list;
    QString path;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("open image"));
    fileDialog->setDirectory(".");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    if(fileDialog->exec())
    {
        path_list = fileDialog->selectedFiles();
    }
    path = path_list[0];
    ui->lb_image_path->setText(path);


    QImage *img=new QImage;
    img->load(path);
    ui->lb_image->setPixmap(QPixmap::fromImage(*img));
}
