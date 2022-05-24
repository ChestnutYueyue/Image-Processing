#ifndef WIDGET_H
#define WIDGET_H

#include "mythread.h"
#include <QDebug>
#include <QFileDialog>
#include <QThreadPool>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  void button();

private:
  Ui::Widget *ui;
  QString file_path;
  QStringList file_list;
  QStringList filename;
  QDir dir;
  size_t size;
  bool is_button, is_dispose;
};
#endif // WIDGET_H
