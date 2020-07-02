#include "gamewidget_2.h"

GameWidget_2::GameWidget_2(QWidget *parent) :   // Constructor
    QWidget(parent),
    timer(new QTimer(this)),
    elasticNeuralNet(this->cities)
//    ElasticNet constructor
{

    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}




GameWidget_2::~GameWidget_2()   // Destructor
{

}

void GameWidget_2::startGame(const int &number)  // Start Game
{
    emit gameStarts(true);
     if (!this->networkRunning) {
         wd_same = 0;
     //    generations = number;
         generationsCount = 0;
      //   elasticNeuralNet = ENN(cities, alpha, beta, K);
         elasticNeuralNet = ENN(cities, this->alpha, this->beta, this->k, this->kUpdatePeriod, this->radius, this->numPointFactor);
         points = elasticNeuralNet.getNetworkPoints();
     }

    this->networkRunning = true;
    emit environmentChanged(true);
    timer->start();
    this->networkRunning = true;
}

void GameWidget_2::stopGame()  //Stop Game
{
    timer->stop();
}

void GameWidget_2::clear() // Clear game field
{
    //
    emit gameEnds(true);
    this->networkRunning = false;
    this->points->clear();
    update();

}

void GameWidget_2::clearCities() // Clear game field
{
    //
    emit gameEnds(true);
    this->networkRunning = false;
    this->cities->clear();
    update();

}

int GameWidget_2::interval() // Interval between generations
{
    return timer->interval();
}


void GameWidget_2::setGenerations(int in) //set generations
{
    this->generations = abs(in);
}

void GameWidget_2::setInterval(int msec) // Set interval between generations
{
    timer->setInterval(msec);
}

std::vector<City>* GameWidget_2::getCities(){

    return this->cities;

}

void GameWidget_2::setAlpha(double in)  // Set Alpha parameter of the algorithm
{
    this->alpha = in;

}

void GameWidget_2::setBeta(double in)   // Set Beta parameter of the algorithm
{
    this->beta = in;
}

void GameWidget_2::setGamma(double in)  // Set Alpha parameter of the algorithm
{
}

void GameWidget_2::setK(double in)  // Set K parameter of the algorithm
{
    this->k = in;

}

void GameWidget_2::setKUpdatePeriod(int in) {
    this->kUpdatePeriod = in;
}

void GameWidget_2::setRadius(double in) {
    this->radius = in;
}

void GameWidget_2::setNumPointFactor(double in) {
    this->numPointFactor = in;
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
    GameWidget_2::AddCity(c_x/fieldX, c_y/fieldY);
    update();
}

void GameWidget_2::AddCity(float x, float y)
{
    float fieldX = width();
    float fieldY = height();
    emit environmentChanged(true);
    int size = this->cities->size() + 1;
    //std::cout << "X: " << city->x << " Y: " << city->y << std::endl;
    //std::cout << city->magnitude() << std::endl;
    this->cities->push_back(City(x,y,size));
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
    for(std::vector<City>::iterator itC = this->cities->begin(); itC != this->cities->end(); ++itC) {
        double x = itC->x;
        double y = itC->y;
        p.drawEllipse(fieldX*x-3.5, fieldY*y-3.5, 7, 7);
    }
}

void GameWidget_2::paintNet(QPainter &p)    // Draw elastic net in the current state
{
    float fieldX = width();
    float fieldY = height();
    p.setBrush(QBrush(Qt::red, Qt::SolidPattern));

    for(std::vector<NetworkPoint>::iterator itP = this->points->begin(); itP != this->points->end(); ++itP)  {
        //float pX, pY;

        float p_x = itP->x * fieldX;
        float p_y = itP->y * fieldY;
        p.drawEllipse(p_x-2.5, p_y-2.5, 5, 5);
        std::vector<NetworkPoint>::iterator nextPoint = itP+1;
        if ( nextPoint == this->points->end() ) nextPoint = this->points->begin();

        //  float pX2, pY2;

        float p_x2 = nextPoint->x * fieldX;
        float p_y2 = nextPoint->y * fieldY;
        p.drawEllipse(p_x2-2.5, p_y2-2.5, 5, 5);
        p.drawLine(p_x, p_y, p_x2, p_y2);
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
    elasticNeuralNet.optimizeNetworkPoints();
    update();
}

void GameWidget_2::newGeneration()  // Start the evolution of elastic net and update the game field
{
    if( generationsCount >= generations) {    // Exit function if evolution is finished (worst distance is low) or if number of iteration is too high

        emit gameEnds(true);
        stopGame();
        return;
    }
    int interval = 1;

    for( int i = 0; i < interval; i++ ) {   // Increasing the number of iterations per generation to make visualisation faster
        elasticNeuralNet.optimizeNetworkPoints();
    }

    emit newGeneration(++generationsCount);
    update();
}

float GameWidget_2::CalcDist()
{
  float dist = 0;

  return dist;
}
