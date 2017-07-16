#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "configfiledao.h"

namespace Ui {
class DisplayTab;
}

class DisplayTab : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayTab(string vendorId, string productId, QWidget *parent = 0);
    ~DisplayTab();

private slots:
    void on_addNewResolutionButton_clicked();

    void on_removeNewResolutionButton_clicked();

    void on_refreshResolutionListButton_clicked();

    void on_debugButton_clicked();

private:
    Ui::DisplayTab* ui;
    ConfigFileDao* configFileDao = new ConfigFileDao();

    void refreshResolutionList(string vendorId, string productId);
};

#endif // MAINDIALOG_H
