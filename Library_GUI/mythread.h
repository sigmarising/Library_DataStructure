#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

public:

    MyThread();

    void stop();

protected:

    void run();

private:

    volatile bool stopped;

};

#endif // MYTHREAD_H
