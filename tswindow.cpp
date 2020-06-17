#include "tswindow.h"
#include "ui_tswindow.h"

TSWindow::TSWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TSWindow)
{
    ui->setupUi(this);
}

TSWindow::~TSWindow()
{
    delete ui;
}

