#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
//    game(new GameWidget(this)),
    game2(new GameWidget_2(this))
{

    ui->setupUi(this);                              //Fill in the drop-down list with the types of evolution
    ui->doubleSpinBox->setValue(game2->getAlpha());
    ui->doubleSpinBox_2->setValue(game2->getBeta());
    ui->doubleSpinBox_3->setValue(game2->getK());
    ui->kUpdatePeriodBox->setValue(game2->getKUpdatePeriod());
    ui->radiusBox->setValue(game2->getRadius());
    ui->numPointFactorBox->setValue(game2->getNumPointFactor());
    ui->maxGenerationsBox->setValue(game2->getGenerations());

    QPixmap icon(16, 16);
    icon.fill(currentColor);

    connect(ui->loadButton_2, SIGNAL(clicked()), this, SLOT(loadCities()));   // Load Cities with press the button "Load"

    // User interface setup for elastic net TSP task
    ui->mainLayout->setStretchFactor(ui->gameLayout_2, 8);
    ui->gameLayout_2->addWidget(game2);

    connect(ui->runButton2, SIGNAL(clicked()), game2,SLOT(startGame()));                        // Start evolution with press the button "Start"
    connect(ui->stopButton2, SIGNAL(clicked()), game2,SLOT(stopGame()));                        // Stop evolution with press the button "Stop"
    connect(ui->clearButton2, SIGNAL(clicked()), game2,SLOT(clear()));                          // Clear field with press the button "Clear"
    connect(ui->clearCitiesButton, SIGNAL(clicked()) , game2, SLOT(clearCities()));
    connect(ui->iterInterval_3, SIGNAL(valueChanged(int)), game2, SLOT(setInterval(int)));      // Changing the interval between iteration with press the button "Generation interval"
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), game2, SLOT(setAlpha(double)));    // Changing Alpha parameter of the algorithm
    connect(ui->doubleSpinBox_6, SIGNAL(valueChanged(double)), game2, SLOT(setGamma(double)));    // Changing Gamma parameter of the algorithm
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), game2, SLOT(setBeta(double)));   // Changing Beta parameter of the algorithm
    connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), game2, SLOT(setK(double)));      // Changing K parameter of the algorithm
    connect(ui->kUpdatePeriodBox, SIGNAL(valueChanged(int)), game2, SLOT(setKUpdatePeriod(int)));
    connect(ui->radiusBox, SIGNAL(valueChanged(double)), game2, SLOT(setRadius(double)));
    connect(ui->numPointFactorBox, SIGNAL(valueChanged(double)), game2, SLOT(setNumPointFactor(double)));
    connect(ui->maxGenerationsBox, SIGNAL(valueChanged(int)), game2, SLOT(setGenerations(int)));


    connect(game2,SIGNAL(gameStarts(bool)),ui->doubleSpinBox,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->doubleSpinBox,SLOT(setEnabled(bool)));             // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->doubleSpinBox_2,SLOT(setDisabled(bool)));        // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->doubleSpinBox_2,SLOT(setEnabled(bool)));           // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->doubleSpinBox_3,SLOT(setDisabled(bool)));        // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->doubleSpinBox_3,SLOT(setEnabled(bool)));           // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->doubleSpinBox_6,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->doubleSpinBox_6,SLOT(setEnabled(bool)));             // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->kUpdatePeriodBox,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->kUpdatePeriodBox,SLOT(setEnabled(bool)));             // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->radiusBox,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->radiusBox,SLOT(setEnabled(bool)));             // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->numPointFactorBox,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->numPointFactorBox,SLOT(setEnabled(bool)));             // When evolution ended - activate the SpinBox
    connect(game2,SIGNAL(gameStarts(bool)),ui->maxGenerationsBox,SLOT(setDisabled(bool)));          // When evolution started - lock the SpinBox
    connect(game2,SIGNAL(gameEnds(bool)),ui->maxGenerationsBox,SLOT(setEnabled(bool)));
    connect(game2,SIGNAL(gameEnds(bool)),game2,SLOT(stopGame()));

    connect(game2, SIGNAL(newGeneration(int)), ui->lcdNumber, SLOT(display(int)));
    connect(game2, SIGNAL(showDistance(double)), ui->lcdDistance, SLOT(display(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCities()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved cities"),
                                                    QDir::homePath());
    if(filename.length() < 1)
        return;
  TSP tsp(filename.toStdString());
  game2->clearCities();
  game2->clear();
  std::vector<City> *cities = tsp.getCities();
  for( int i = 0; i < int(cities->size()); i++ ) {
    game2->AddCity( cities->at(i).x, cities->at(i).y );
  }
  game2->setScale(tsp.getScale());
/*
  QString filename = QFileDialog::getOpenFileName(this,
                                                  tr("Open saved cities"),
                                                  QDir::homePath());
  if(filename.length() < 1)
      return;

  TSP tsp("filename");

  std::vector<City>* cities = tsp.getCities();

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly))
      return;
  QTextStream in(&file);
  QString t;
  int NC;
  float xmax(-99999), xmin(99999);
  float ymax(-99999), ymin(99999);
  do{
      in >> t;
    } while( t != "DIMENSION:" );
//  in >> t;
  in >> NC;
  float* xc = new float [NC];
  float* yc = new float [NC];
  do{
      in >> t;
    } while( t != "NODE_COORD_SECTION" );
  int n;
  for( int i = 0; i < NC; i++ ) {
      in >> n >> xc[i] >> yc[i];
      if( xc[i] > xmax ) xmax = xc[i];
      if( yc[i] > ymax ) ymax = yc[i];
      if( xc[i] < xmin ) xmin = xc[i];
      if( yc[i] < ymin ) ymin = yc[i];
    }
  game2->fieldSizeX = (xmax - xmin);
  game2->fieldSizeY = (ymax - ymin);*/
}
