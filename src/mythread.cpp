
#include "mythread.h"

MyThread::MyThread(QString filename) : QRunnable() {
  this->p.SetFilename(filename);
  setAutoDelete(true);
}
void MyThread::run() {
  QMutexLocker locker(&mutex);
  this->p.Dispose();
  this->p.Save();
  emit finished(this->p.GetFilename());
}
