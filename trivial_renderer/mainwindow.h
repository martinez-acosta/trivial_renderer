#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tdialog.h"
#include "tmodel.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QString objfile;
  TModel *model;
private slots:
  void createModel();
  void rasterize();
};

#endif // MAINWINDOW_H
