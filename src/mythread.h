#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "processing.h"
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QRunnable>
#include <QString>
#include <QThread>
#include <QWaitCondition>

class MyThread : public QObject, public QRunnable {
  Q_OBJECT
public:
  MyThread(QString filename);
  void run();
signals:
  void finished(QString _message);

private:
  Processing p;
  QMutex mutex;
};

#endif