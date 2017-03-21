#include "mainwindow.h"
#include "tdraw.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QImage>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->actionReadObjfile, &QAction::triggered, this,
          &MainWindow::createModel);
  connect(ui->actionWireframe, &QAction::triggered, this,
          &MainWindow::rasterize);
}

void MainWindow::createModel() {
  QObject *obj = sender();
  QString objName = obj->objectName();

  // Solicitamos archivo obj
  if (!objName.compare(ui->actionReadObjfile->objectName())) {
    objfile = QFileDialog::getOpenFileName(this, tr("Open Objfile"),
                                           tr("Files (*.obj)"));
  }

  model = new TModel(objfile.toStdString());
  model->readObjFile(objfile.toStdString());
  ui->statusBar->showMessage("Modelo actual: " + objfile);
}

void MainWindow::rasterize() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  // Wireframe
  if (!objName.compare(ui->actionWireframe->objectName())) {
    // Transformaciones
    unsigned int imagen[1920 * 1080];

    for (int i = 0; i < 1920 * 1080; i++) {
      imagen[i] = 0xffffffff;
    }

    for (auto &i : model->list_vertexes) {
      i *= 11;
    }
    TDraw draw;
    TVector4D w1, w2, w3;
    TPoint res{1920, 1080};
    // Dibujamos en el framebuffer
    for (auto &i : model->faces_for_vertexes) {

      w1 = model->list_vertexes.at(i.v1 - 1);
      w2 = model->list_vertexes.at(i.v2 - 1);
      w3 = model->list_vertexes.at(i.v3 - 1);
      draw.bresenhamLine(w1.toPoint(), w2.toPoint(), imagen, res);
      draw.bresenhamLine(w2.toPoint(), w3.toPoint(), imagen, res);
      draw.bresenhamLine(w3.toPoint(), w1.toPoint(), imagen, res);
    }

    QImage img(reinterpret_cast<unsigned char *>(imagen), 1920, 1080,
               QImage::Format_ARGB32_Premultiplied);
    img.save("salida.png");
  }
}
MainWindow::~MainWindow() { delete ui; }
