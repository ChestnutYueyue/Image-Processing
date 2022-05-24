#ifndef PROCESSING_H
#define PROCESSING_H
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <opencv2/opencv.hpp>

class Processing : public QObject {
  Q_OBJECT
private:
  cv::Mat _img;
  QString _filename;

public:
  Processing();
  Processing(const QString filename);
  void Dispose();
  void SetFilename(const QString filename);
  void Save();
  QString GetFilename();
  ~Processing();
};
#endif // !PROCESSING_H
