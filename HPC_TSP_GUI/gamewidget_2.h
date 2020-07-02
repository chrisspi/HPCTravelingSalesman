#ifndef GameWidget_2_H
#define GameWidget_2_H

#include <QColor>
#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "QTime"
#include "../cliApp/TSP.h"
#include "../cliApp/ENN.h"
#include "../cliApp/tspvector.h"
#include <cmath>


class GameWidget_2 : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget_2(QWidget *parent = 0);
    ~GameWidget_2();

  float fieldSizeX;
  float fieldSizeY;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);

signals:
    //when one of the cell has been changed,emit this signal to lock the universeSize
    void environmentChanged(bool ok);
    void gameStarts(bool ok);
    void newGeneration(int gen);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

public slots:
    void startGame(const int &number = -1); // start
    void stopGame(); // finish
    void clear(); // clear
    void clearCities(); // clear the cities

    int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations
    void setAlpha(double in);
    void setBeta(double in);
    void setGamma(double in);
    void setK(double in);
    void setKUpdatePeriod(int in);
    void setRadius(double in);
    void setNumPointFactor(double in);
    void setGenerations(int in);

    double getAlpha(){return this->alpha;};
    double getBeta(){return this->beta;};
    double getK(){return this->k;};
    unsigned int getKUpdatePeriod(){return this->kUpdatePeriod;};
    double getRadius(){return this->radius;};
    double getNumPointFactor(){return this->numPointFactor;};
    int getGenerations(){return this->generations;};

    void initPoints();
    void runIteration();

    void AddCity(float x, float y);
    std::vector<City>* getCities();
    float CalcDist();

private slots:
    void paintField(QPainter &p);
    void paintCities(QPainter &p);
    void paintNet(QPainter &p);
    void newGeneration();

private:
    QTimer* timer;

    int generations = 10000;
    unsigned int generationsCount = 0;
//    ElasticNet
    std::vector<City> *cities = new std::vector<City>;
    std::vector<NetworkPoint> *points = new std::vector<NetworkPoint>;
//    TSP travelingSalesman;
    ENN elasticNeuralNet;

    double alpha = 1.0;
    double beta = 1.0;
    double k = 0.1;
    int  kUpdatePeriod = 25;
    double radius = 0.1;
    double numPointFactor = 2.5;

    bool networkRunning = false;


    float wd;
    int wd_same;
};

#endif // GameWidget_2_H
