#include "tabcontainer.h"
#include "ui_tabcontainer.h"
#include "displaytab.h"
#include <QLabel>
#include "displaysao.h"
#include <QKeyEvent>
#include <qdebug.h>
#include <cstdlib>
#include "utils.cpp"

TabContainer::TabContainer(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ContainerTab)
{
    ui->setupUi(this);

    //设置使用说明的url
    ui->helpPage->setUrl(QUrl("http://czzshr.github.io/post/hellodpi-instruction"));

    //查看当前有几个屏幕
    DisplaySao* displaySao = new DisplaySao();
    vector<pair<string, string>>* vendorIdProductIdPairList = displaySao->getVendorIdProductIdPairList();

    //每个屏幕在主界面上添加一个tab
    int i = 1;
    int tabIndex = 0;
    for (pair<string, string> pair : *vendorIdProductIdPairList)
    {
//        cout << pair.first << endl;
//        cout << pair.second << endl;
        string vendorId = pair.first;
        string productId = pair.second;
        this->insertTab(tabIndex++, new DisplayTab(vendorId, productId), QString::fromStdString("显示器" + std::to_string(i++)));
    }

}

TabContainer::~TabContainer()
{
    delete ui;
}

//cmd + w 退出程序
void TabContainer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W && event->modifiers() == Qt::ControlModifier)
    {
        this->close();
    }
}
