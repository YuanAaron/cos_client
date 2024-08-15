#ifndef TRANSFER_H
#define TRANSFER_H

#include <QWidget>

#include <src/fend/uicommon/cosdialog.h>

namespace Ui {
class Transfer;
}

class Transfer : public CosDialog
{
    Q_OBJECT

public:
    explicit Transfer(QWidget *parent = nullptr);
    ~Transfer();

private:
    Ui::Transfer *ui;
};

#endif // TRANSFER_H
