#ifndef RECEIPTEDITDIALOG_H
#define RECEIPTEDITDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "ReceiptTableModel.h"

namespace Ui {
class ReceiptEditDialog;
}

class ReceiptEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiptEditDialog(QWidget *parent = nullptr);
    ~ReceiptEditDialog();

    void setModel(ReceiptTableModel * const receiptModel, QSqlTableModel * const purchaseModel);
    void setCurrentReceiptIndex(const QModelIndex &receiptIndex);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ReceiptEditDialog *ui;
};

#endif // RECEIPTEDITDIALOG_H
