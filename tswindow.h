#ifndef TSWINDOW_H
#define TSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TSWindow; }
QT_END_NAMESPACE

class TSWindow : public QMainWindow
{
    Q_OBJECT

public:
    TSWindow(QWidget *parent = nullptr);
    ~TSWindow();

private:
    Ui::TSWindow *ui;
};
#endif // TSWINDOW_H
