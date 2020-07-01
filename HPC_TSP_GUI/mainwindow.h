#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "gamewidget_2.h"
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "../cliApp/TSP.h"
#include "../cliApp/ENN.h"
#include "../cliApp/tspvector.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void loadCities();
    
private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget_2* game2;
};

#endif // MAINWINDOW_H
