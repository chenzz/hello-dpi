#include "displaytab.h"
#include "ui_displaytab.h"
#include "displaysao.h"
#include "configfiledao.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <vector>
#include <utils.cpp>

DisplayTab::DisplayTab(string vendorId, string productId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayTab)
{
    ui->setupUi(this);
    ui->vendorIdLineEdit->setText(QString::fromStdString(vendorId));
    ui->productIdLineEdit->setText(QString::fromStdString(productId));

    refreshResolutionList(vendorId, productId);
    ui->debugButton->setVisible(false);
}

DisplayTab::~DisplayTab()
{
    delete ui;
}

//刷新分辨率列表
void DisplayTab::refreshResolutionList(string vendorId, string productId)
{

    //删除原有列表
    Utils::clearLayout(ui->resolutionListLayout);

    //列出分辨率列表
    vector<pair<string, string>*> *resolutionList = configFileDao->getResolutionList(stoi(vendorId), stoi(productId));
    if (NULL == resolutionList)
    {
        QMessageBox::critical(this, "错误", "无法解析系统配置文件");
        exit(-1);
    }
    for (pair<string, string>* resolutionItem : *resolutionList)
    {
        QLayout* resolutionItemLayout = new QHBoxLayout();

        QLineEdit* widthLineEdit = new QLineEdit();
        widthLineEdit->setText(QString::fromStdString(resolutionItem->first));
        widthLineEdit->setReadOnly(true);
        widthLineEdit->setFixedWidth(50);

        QLabel* label = new QLabel();
        label->setText("x");

        QLineEdit* heightLineEdit = new QLineEdit();
        heightLineEdit->setText(QString::fromStdString(resolutionItem->second));
        heightLineEdit->setReadOnly(true);
        heightLineEdit->setFixedWidth(50);

        resolutionItemLayout->addWidget(widthLineEdit);
        resolutionItemLayout->addWidget(label);
        resolutionItemLayout->addWidget(heightLineEdit);
        ui->resolutionListLayout->addLayout(resolutionItemLayout);
    }

//    ui->resolutionListLayout->addWidget(new QLabel("test"));

//    QLayoutItem *item = ui->resolutionListLayout->takeAt(0);
//    if (item != NULL)
//    {
//        delete item;
//    }

//    QDialog * dialog = new QDialog();
//    QVBoxLayout* layout = new QVBoxLayout(this);
//    layout->addWidget(new QLabel("test2"));

//    layout->takeAt(0);
//    dialog->show();

}

void DisplayTab::on_addNewResolutionButton_clicked()
{
    QString vendorIdString = ui->vendorIdLineEdit->text();
    QString productIdString = ui->productIdLineEdit->text();
    QString newWidth = ui->newWidthLineEdit->text();
    QString newHeight = ui->newHeightLineEdit->text();

    if (newWidth.isEmpty() || newHeight.isEmpty())
    {
        QMessageBox::warning(this, "警告", "输入不能为空！");
        return;
    }

    configFileDao->addResolutionItem(vendorIdString.toInt(), productIdString.toInt(), pair<string, string>(newWidth.toStdString(), newHeight.toStdString()));

    QString vendorId = ui->vendorIdLineEdit->text();
    QString productId = ui->productIdLineEdit->text();
    refreshResolutionList(vendorId.toStdString(), productId.toStdString());
}




//删除分辨率配置项
void DisplayTab::on_removeNewResolutionButton_clicked()
{
    QString vendorIdString = ui->vendorIdLineEdit->text();
    QString productIdString = ui->productIdLineEdit->text();
    QString newWidth = ui->newWidthLineEdit->text();
    QString newHeight = ui->newHeightLineEdit->text();

    if (newWidth.isEmpty() || newHeight.isEmpty())
    {
        QMessageBox::warning(this, "警告", "输入不能为空！");
        return;
    }
    configFileDao->removeResolutionItem(vendorIdString.toInt(), productIdString.toInt(), pair<string, string>(newWidth.toStdString(), newHeight.toStdString()));
    refreshResolutionList(vendorIdString.toStdString(), productIdString.toStdString());
}

//刷新分辨率配置列表
void DisplayTab::on_refreshResolutionListButton_clicked()
{
    QString vendorIdString = ui->vendorIdLineEdit->text();
    QString productIdString = ui->productIdLineEdit->text();

    refreshResolutionList(vendorIdString.toStdString(), productIdString.toStdString());
}

void DisplayTab::on_debugButton_clicked()
{
    QLayoutItem * item = ui->resolutionListLayout->takeAt(0);
//    if (item != NULL)
//    {
//        delete item;
//    }
}
