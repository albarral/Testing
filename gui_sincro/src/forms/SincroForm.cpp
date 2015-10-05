/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include <QDebug>
#include <QString>

#include "SincroForm.h"

SincroForm::SincroForm() 
{
    widget.setupUi(this);
    // test
    connect(widget.butON, SIGNAL(clicked()), this, SLOT(clicked_butON()));
    connect(widget.butOFF, SIGNAL(clicked()), this, SLOT(clicked_butOFF()));
    // Heart
    connect(widget.butHeartDown, SIGNAL(clicked()), this, SLOT(clicked_butHeartDown()));
    connect(widget.butHeartUp, SIGNAL(clicked()), this, SLOT(clicked_butHeartUp()));
    // job 1
    connect(widget.but1Start, SIGNAL(clicked()), this, SLOT(clicked_but1Start()));
    connect(widget.but1Stop, SIGNAL(clicked()), this, SLOT(clicked_but1Stop()));
    connect(widget.but1DoOne, SIGNAL(clicked()), this, SLOT(clicked_but1DoOne()));
    connect(widget.but1DoTwo, SIGNAL(clicked()), this, SLOT(clicked_but1DoTwo()));
    // job 2                
    connect(widget.but2Start, SIGNAL(clicked()), this, SLOT(clicked_but2Start()));
    connect(widget.but2Stop, SIGNAL(clicked()), this, SLOT(clicked_but2Stop()));
    connect(widget.but2DoOne, SIGNAL(clicked()), this, SLOT(clicked_but2DoOne()));
    connect(widget.but2DoTwo, SIGNAL(clicked()), this, SLOT(clicked_but2DoTwo()));
    // job 3
    connect(widget.but3Start, SIGNAL(clicked()), this, SLOT(clicked_but3Start()));
    connect(widget.but3Stop, SIGNAL(clicked()), this, SLOT(clicked_but3Stop()));
    connect(widget.but3DoOne, SIGNAL(clicked()), this, SLOT(clicked_but3DoOne()));
    connect(widget.but3DoTwo, SIGNAL(clicked()), this, SLOT(clicked_but3DoTwo()));
    // job 4
    connect(widget.but4Start, SIGNAL(clicked()), this, SLOT(clicked_but4Start()));
    connect(widget.but4Stop, SIGNAL(clicked()), this, SLOT(clicked_but4Stop()));
    connect(widget.but4DoOne, SIGNAL(clicked()), this, SLOT(clicked_but4DoOne()));
    connect(widget.but4DoTwo, SIGNAL(clicked()), this, SLOT(clicked_but4DoTwo()));

    oThread = new QThread;
    oSincroTest = new SincroTest(4);
    launchWorker();
}

SincroForm::~SincroForm() 
{
    endWorker();
    delete (oSincroTest);
}

void SincroForm::launchWorker()
{        
    SincroWorker* oSincroWorker = new SincroWorker(oSincroTest);
    oSincroWorker->moveToThread(oThread);
    
    // default signals
    connect(oThread, SIGNAL(finished()), oThread, SLOT(deleteLater()));
    connect(oSincroWorker, SIGNAL(finished()), oSincroWorker, SLOT(deleteLater()));
    connect(oSincroWorker, SIGNAL(finished()), oThread, SLOT(quit()));

    // form -> worker
    connect(this, SIGNAL(worker_start()), oSincroWorker, SLOT(process()));
    connect(this, SIGNAL(worker_stop()), oSincroWorker, SLOT(stop()));
    // worker -> form
    connect(oSincroWorker, SIGNAL(refreshGUI(SincroWorker::st_guiData*, int)), this, SLOT(showData(SincroWorker::st_guiData*, int)));
    
    oThread->start();
    emit worker_start();
}


void SincroForm::endWorker()
{        
    emit worker_stop();
    usleep(1000000);
    oThread->quit();
}

// SLOTS SECTION ...

void SincroForm::clicked_butON() {oSincroTest->startAll();}
void SincroForm::clicked_butOFF() {oSincroTest->stopAll();}
// Heart
void SincroForm::clicked_butHeartUp() {oSincroTest->heartUp();}
void SincroForm::clicked_butHeartDown() {oSincroTest->heartDown();}

// job1
void SincroForm::clicked_but1Start() {oSincroTest->start(0);}
void SincroForm::clicked_but1Stop() {oSincroTest->stop(0);}
void SincroForm::clicked_but1DoOne() {oSincroTest->doOne(0);}
void SincroForm::clicked_but1DoTwo() {oSincroTest->doTwo(0);}
// job2
void SincroForm::clicked_but2Start() {oSincroTest->start(1);}
void SincroForm::clicked_but2Stop() {oSincroTest->stop(1);}
void SincroForm::clicked_but2DoOne() {oSincroTest->doOne(1);}
void SincroForm::clicked_but2DoTwo() {oSincroTest->doTwo(1);}
// job3
void SincroForm::clicked_but3Start() {oSincroTest->start(2);}
void SincroForm::clicked_but3Stop() {oSincroTest->stop(2);}
void SincroForm::clicked_but3DoOne() {oSincroTest->doOne(2);}
void SincroForm::clicked_but3DoTwo() {oSincroTest->doTwo(2);}
// job4
void SincroForm::clicked_but4Start() {oSincroTest->start(3);}
void SincroForm::clicked_but4Stop() {oSincroTest->stop(3);}
void SincroForm::clicked_but4DoOne() {oSincroTest->doOne(3);}
void SincroForm::clicked_but4DoTwo() {oSincroTest->doTwo(3);}


void SincroForm::showData(SincroWorker::st_guiData* data, int rythm)
{    
    showDataJob1(&data[0]);
    showDataJob2(&data[1]);
    showDataJob3(&data[2]);
    showDataJob4(&data[3]);
    widget.LCDHeart->display(rythm);
}


void SincroForm::showDataJob1(SincroWorker::st_guiData* jobData)
{
    QString qs;
    qs.setNum(jobData->state);
    widget.field1State->setText(qs);
    widget.LCD1TargetF->display(jobData->tarFreq);
    widget.LCD1RealF->display(jobData->realFreq);

    switch(jobData->devSign)
    {
        case 1:
            widget.bar1DeviationP->setValue(jobData->devFraction);
            widget.bar1DeviationN->setValue(0);
            break;
        case -1:
            widget.bar1DeviationN->setValue(jobData->devFraction);
            widget.bar1DeviationP->setValue(0);
            break;            
    }
    
    widget.bar1WaitTime->setValue(jobData->waitFraction);
}

void SincroForm::showDataJob2(SincroWorker::st_guiData* jobData)
{
    QString qs;
    qs.setNum(jobData->state);
    widget.field2State->setText(qs);
    widget.LCD2TargetF->display(jobData->tarFreq);
    widget.LCD2RealF->display(jobData->realFreq);

    switch(jobData->devSign)
    {
        case 1:
            widget.bar2DeviationP->setValue(jobData->devFraction);
            widget.bar2DeviationN->setValue(0);
            break;
        case -1:
            widget.bar2DeviationN->setValue(jobData->devFraction);
            widget.bar2DeviationP->setValue(0);
            break;            
    }
    
    widget.bar2WaitTime->setValue(jobData->waitFraction);
}

void SincroForm::showDataJob3(SincroWorker::st_guiData* jobData)
{
    QString qs;
    qs.setNum(jobData->state);
    widget.field3State->setText(qs);
    widget.LCD3TargetF->display(jobData->tarFreq);
    widget.LCD3RealF->display(jobData->realFreq);

    switch(jobData->devSign)
    {
        case 1:
            widget.bar3DeviationP->setValue(jobData->devFraction);
            widget.bar3DeviationN->setValue(0);
            break;
        case -1:
            widget.bar3DeviationN->setValue(jobData->devFraction);
            widget.bar3DeviationP->setValue(0);
            break;            
    }
    
    widget.bar3WaitTime->setValue(jobData->waitFraction);
}

void SincroForm::showDataJob4(SincroWorker::st_guiData* jobData)
{
    QString qs;
    qs.setNum(jobData->state);
    widget.field4State->setText(qs);
    widget.LCD4TargetF->display(jobData->tarFreq);
    widget.LCD4RealF->display(jobData->realFreq);

    switch(jobData->devSign)
    {
        case 1:
            widget.bar4DeviationP->setValue(jobData->devFraction);
            widget.bar4DeviationN->setValue(0);
            break;
        case -1:
            widget.bar4DeviationN->setValue(jobData->devFraction);
            widget.bar4DeviationP->setValue(0);
            break;            
    }
    
    widget.bar4WaitTime->setValue(jobData->waitFraction);
}

void SincroForm::errorString(QString err)
{
    qDebug() << err;
}