#include "processing.h"
Processing::Processing() {}
Processing::Processing(const QString filename) { _filename = filename; }
void Processing::Dispose() {
  // 创建一个QImage对象
  _img = cv::imread(_filename.toStdString().c_str(), 0);
  // 高斯模糊
  cv::GaussianBlur(_img, _img, cv::Size(1, 1), 0, 0);
  // 锐化
  cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 6, -1, 0, -1, 0);
  cv::filter2D(_img, _img, _img.depth(), kernel);
  // 自适应二值化
  cv::adaptiveThreshold(_img, _img, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                        cv::THRESH_BINARY_INV, 55, 15);
  // 膨胀
  cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1), cv::Point(-1, -1));
  cv::morphologyEx(_img, _img, cv::MORPH_CLOSE, element);
  cv::dilate(_img, _img, element);
  // 反转
  cv::bitwise_not(_img, _img);
  cv::bitwise_and(_img, _img, _img, cv::Mat());
  cv::add(_img, cv::Scalar(1), _img);
}
void Processing::Save() {
  // 获取文件名
  QString name = QFileInfo(_filename).fileName();
  // 获取文件路径
  QString path = QFileInfo(_filename).canonicalPath();
  name = "已处理_" + name;
  // 路径+文件名
  _filename = path + "/" + name;
  // 保存
  cv::imwrite(_filename.toStdString().c_str(), _img);
}
void Processing::SetFilename(const QString filename) { _filename = filename; }
QString Processing::GetFilename() { return QFileInfo(_filename).fileName(); }
Processing::~Processing() {
  // 销毁所有资源
  cv::destroyAllWindows();
}