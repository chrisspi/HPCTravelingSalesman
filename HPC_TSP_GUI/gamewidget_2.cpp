#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "gamewidget_2.h"
#include "QTime"


GameWidget_2::GameWidget_2(QWidget *parent) :   // Constructor
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1)
//    ElasticNet constructor
{
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}
    vector<City> *cities = new vector<City>;



GameWidget_2::~GameWidget_2()   // Destructor
{

}

void GameWidget_2::startGame(const int &number)  // Start Game
{
    emit gameStarts(true);
    wd_same = 0;
    generations = number;
    timer->start();
}

void GameWidget_2::stopGame()  //Stop Game
{
    timer->stop();
}

void GameWidget_2::clear() // Clear game field
{
    //
    emit gameEnds(true);
    cities->clear();
    update();

}

int GameWidget_2::interval() // Interval between generations
{
    return timer->interval();
}

void GameWidget_2::setInterval(int msec) // Set interval between generations
{
    timer->setInterval(msec);
}

vector<City> GameWidget_2::getCities(){

    return *cities;

}

void GameWidget_2::setAlpha(double in)  // Set Alpha parameter of the algorithm
{

}

void GameWidget_2::setBeta(double in)   // Set Beta parameter of the algorithm
{

}

void GameWidget_2::setGamma(double in)  // Set Alpha parameter of the algorithm
{

}

void GameWidget_2::setK(double in)  // Set K parameter of the algorithm
{

}

void GameWidget_2::paintEvent(QPaintEvent *)    // Draw all cities and elastic net on the screen
{
    QPainter p(this);
    paintField(p);
    paintCities(p);
    paintNet(p);
}

void GameWidget_2::mousePressEvent(QMouseEvent *e)  // Add new city to the firld
{
    emit environmentChanged(true);
    float c_x = e->x();
    float c_y = e->y();
    float fieldX = width();
    float fieldY = height();

    update();
}

void GameWidget_2::AddCity(float x, float y)
{
  emit environmentChanged(true);

  update();
}

void GameWidget_2::paintField(QPainter &p)  // Draw game field
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    p.setPen(Qt::black);
    p.setBrush(Qt::white);
    p.drawRect(borders);
}

void GameWidget_2::paintCities(QPainter &p) // Draw cities
{
    float fieldX = width();
    float fieldY = height();
    p.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    for( int iCity = 0; iCity < 0; iCity++ ) {
        float cX, cY;

        float c_x = 0;
        float c_y = 0;
        p.drawEllipse(c_x-3.5, c_y-3.5, 7, 7);
    }


}

void GameWidget_2::paintNet(QPainter &p)    // Draw elastic net in the current state
{
    float fieldX = width();
    float fieldY = height();
    p.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    if( 0 ) {
        for( int iPoint = 0; iPoint < 0; iPoint++ ) {
            float pX, pY;

            float p_x = 0;
            float p_y = 0;
            p.drawEllipse(p_x-2.5, p_y-2.5, 5, 5);
            int nextPointIndex = 0;
            float pX2, pY2;

            float p_x2 = 0;
            float p_y2 = 0;
            p.drawLine(p_x, p_y, p_x2, p_y2);
        }
    }
}

void GameWidget_2::initPoints()
{
    if( 0 ) {

    }
    update();
}

void GameWidget_2::runIteration()   // Run one iteration of the algorithm
{
    if( 0 ) {

    }
    update();
}

void GameWidget_2::newGeneration()  // Start the evolution of elastic net and update the game field
{
    if( 0 ) {    // Exit function if evolution is finished (worst distance is low) or if number of iteration is too high

        emit gameEnds(true);
        return;
    }
    int interval = 1;

    if( 0 ) {
        for( int i = 0; i < interval; i++ ) {   // Increasing the number of iterations per generation to make visualisation faster
//            ElasticNet iteration
        }
    }
    update();
}

float GameWidget_2::CalcDist()
{
  float dist = 0;

  return dist;
}
