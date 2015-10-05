/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Cell.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    thread = new QThread();
    worker = new Worker();
    
    worker->moveToThread(thread);
    connect(ui->buttonIniciar, SIGNAL(released()),this, SLOT(start()));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    
    setScene();
}

MainWindow::~MainWindow() 
{
    worker->abort();
    thread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete thread;
    delete worker;

    delete ui;
}

void MainWindow::setScene()
{
    scene = new QGraphicsScene(this);
    ui->boardView->setScene(scene);
    
    scene->setBackgroundBrush(QColor::fromRgb(128,128,128));
   
    QColor whitesmoke(QColor::fromRgb(245,245,245));
    QColor mediumblue(QColor::fromRgb(65,105,225));
    
    Cell *cell00 = new Cell(00, mediumblue, 0, 0);
    scene->addItem(cell00);
    Cell *cell01 = new Cell(01, whitesmoke, 111, 0);
    scene->addItem(cell01);
    Cell *cell02 = new Cell(02, mediumblue, 223, 0);
    scene->addItem(cell02);
    Cell *cell10 = new Cell(10, whitesmoke, 0, 111);
    scene->addItem(cell10);
    Cell *cell11 = new Cell(11, mediumblue, 111, 111);
    scene->addItem(cell11);
    Cell *cell12 = new Cell(12, whitesmoke, 223, 111);
    scene->addItem(cell12);
    Cell *cell20 = new Cell(20, mediumblue, 0, 223);
    scene->addItem(cell20);
    Cell *cell21 = new Cell(21, whitesmoke, 111, 223);
    scene->addItem(cell21);
    Cell *cell22 = new Cell(22, mediumblue, 223, 223);
    scene->addItem(cell22);
    
    ui->boardView->setScene(scene); 
}

void MainWindow::start()
{
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    
    // Clean the board
    
    //Ask who wants to start
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Start", "Do you want to start the game?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        
    } else {
        
    }
    
    worker->requestWork();
   
}