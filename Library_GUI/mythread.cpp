#include "mythread.h"
#include "dmain1.h"
#include "global_define.h"
#include <QTime>

extern DMain1 *w1_1;

MyThread::MyThread()
{
    stopped = false;
}

void MyThread::stop(){

    stopped = true;

}

void MyThread::run(){
    QTime Time_Now;

    while (!stopped){
        Time_Now = QTime::currentTime();
        int during = Time_Start.msecsTo(Time_Now);
        if(during >= 7000){
            w1_1->Day_Add();
            Time_Start = QTime::currentTime();
        }

    }

    stopped = false;
}
