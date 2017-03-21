#ifndef TDIALOG_H
#define TDIALOG_H
#include "tvector4d.h"
#include <QDialog>

namespace Ui {
class TDialog;
}

class TDialog : public QDialog {
  Q_OBJECT

public:
  explicit TDialog(QWidget *parent = 0);
  void getOptions();
  ~TDialog();
  TVector3D rotate;
  TVector3D translate;
  TVector4D scale;
  TPoint vp, vq;

private:
  bool do_rotation;
  bool do_translation;
  bool do_scale;
  bool do_viewport;
  Ui::TDialog *ui;
};

#endif // TDIALOG_H
