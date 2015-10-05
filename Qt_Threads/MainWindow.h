#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <QMainWindow>
#include <QThread>

#include "ui_MainWindow.h"
#include "Worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QThread *thread;
    Worker *worker;
    
    QGraphicsScene *scene;
    QGraphicsView *view;
        
private slots:
    void setScene();
    void start();
    
};

#endif	/* _MAINWINDOW_H */
