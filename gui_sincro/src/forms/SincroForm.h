/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#ifndef _SINCROFORM_H
#define	_SINCROFORM_H

#include <QThread>

#include "ui_SincroForm.h"
#include "workers/SincroWorker.h"
#include "test/test_sincro.h"

class SincroForm : public QDialog 
{
    Q_OBJECT
   
    private:
    Ui::SincroForm widget;
    QThread* oThread;
    SincroTest* oSincroTest;

    public:
    SincroForm();
    virtual ~SincroForm();
      
    public slots:
        void clicked_butON();
        void clicked_butOFF();
        
        void clicked_butHeartUp();
        void clicked_butHeartDown();

        void clicked_but1Start();
        void clicked_but1Stop();
        void clicked_but1DoOne();
        void clicked_but1DoTwo();

        void clicked_but2Start();
        void clicked_but2Stop();
        void clicked_but2DoOne();
        void clicked_but2DoTwo();

        void clicked_but3Start();
        void clicked_but3Stop();
        void clicked_but3DoOne();
        void clicked_but3DoTwo();

        void clicked_but4Start();
        void clicked_but4Stop();
        void clicked_but4DoOne();
        void clicked_but4DoTwo();
        
        void errorString(QString err);
        
        void showData(SincroWorker::st_guiData* data, int rythm);
        
    signals:
        void worker_start();
        void worker_stop();

    private:
        void launchWorker();
        void endWorker();
        void showDataJob1(SincroWorker::st_guiData* jobData);
        void showDataJob2(SincroWorker::st_guiData* jobData);
        void showDataJob3(SincroWorker::st_guiData* jobData);
        void showDataJob4(SincroWorker::st_guiData* jobData);
      
};

#endif	/* _SINCROFORM_H */
