#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), is_button(false), is_dispose(false) {
  ui->setupUi(this);
  this->button();
}
void Widget::button() {
  connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
    ui->textBrowser->clear();
    this->file_list.clear();
    this->file_path = QFileDialog::getExistingDirectory(this, "open", "");
    if (!this->file_list.isEmpty()) {
      ui->path_text->setText(this->file_path);
      filename << "*.png"
               << "*.jpg"
               << "*.jpeg";
      dir.setPath(this->file_path);
      this->file_list =
          dir.entryList(filename, QDir::Files | QDir::Readable, QDir::Name);
      this->size = this->file_list.size();
      for (auto &i : this->file_list) {
        ui->textBrowser->append("已添加文件：" + i);
        i = dir.absoluteFilePath(i);
      }
      this->is_button = true;
    } else {
      ui->textBrowser->append("请选择文件夹");
    }
  });
  connect(ui->pushButton_2, &QPushButton::clicked, this, [=]() {
    ui->textBrowser->clear();
    this->file_list.clear();
    this->file_list =
        QFileDialog::getOpenFileNames(this, "open", "", "(*.jpeg *.jpg *.png)");
    if (!this->file_list.isEmpty()) {
      this->size = this->file_list.size();
      ui->path_text->setText(QFileInfo(this->file_list[0]).canonicalPath());
      for (auto &i : this->file_list) {
        ui->textBrowser->append("已添加文件：" + QFileInfo(i).fileName());
      }
      this->is_button = true;
    } else {
      ui->textBrowser->append("未选择文件");
      return;
    }
  });
  connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() {
    ui->textBrowser->clear();
    if (this->is_button) {
      is_dispose = true;
      for (auto &i : this->file_list) {
        MyThread *thread = new MyThread(i);
        QThreadPool::globalInstance()->start(thread);
        connect(thread, &MyThread::finished, this,
                [=](QString message) { ui->textBrowser->append(message); });
      }
    } else {
      ui->textBrowser->append("请先选择文件或者文件夹");
    }
  });
  connect(ui->pushButton_4, &QPushButton::clicked, this, [=]() {
    if (is_dispose) {
      ui->textBrowser->clear();
      is_dispose = false;
      QThreadPool::globalInstance()->clear();
      for (auto &i : this->file_list) {
        dir.remove(i);
      }
      ui->textBrowser->append("清理完成");
    } else {
      ui->textBrowser->clear();
      ui->textBrowser->append("请先处理文件");
    }
  });
}
Widget::~Widget() { delete ui; }
