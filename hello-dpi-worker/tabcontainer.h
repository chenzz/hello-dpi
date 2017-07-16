#ifndef CONTAINERTAB_H
#define CONTAINERTAB_H

#include <QTabWidget>

namespace Ui {
class ContainerTab;
}

class TabContainer : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabContainer(QWidget *parent = 0);
    ~TabContainer();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    Ui::ContainerTab *ui;
};

#endif // CONTAINERTAB_H
