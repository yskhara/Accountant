#ifndef RECEIPTEDITWIDGET_H
#define RECEIPTEDITWIDGET_H

#include "ReceiptTableModel.h"

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class ReceiptEditWidget;
}

class ReceiptEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiptEditWidget(QWidget *parent = nullptr);
    ~ReceiptEditWidget();

    void setModel(ReceiptTableModel * const receiptModel, QSqlTableModel * const purchaseModel);
    void setCurrentReceiptIndex(const QModelIndex &receiptIndex);
    void submit(void);
    void revert(void);

private:
    Ui::ReceiptEditWidget *ui;
    ReceiptTableModel *model;
    QDataWidgetMapper *mapper;
    //QModelIndex &selectedReceiptIndex;
};

#endif // RECEIPTEDITWIDGET_H
