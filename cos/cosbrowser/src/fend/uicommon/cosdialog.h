#ifndef COSDIALOG_H
#define COSDIALOG_H

#include "basedialog.h"

namespace Ui {
class CosDialog;
}

class CosDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit CosDialog(QWidget *parent = nullptr);
    ~CosDialog();

private:
    Ui::CosDialog *ui;
};

#endif // COSDIALOG_H
