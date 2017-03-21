#include "tdialog.h"
#include "ui_dialog.h"

TDialog::TDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TDialog) {
  ui->setupUi(this);
}
void TDialog::getOptions() {}
TDialog::~TDialog() { delete ui; }
