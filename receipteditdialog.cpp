#include "receipteditdialog.h"
#include "ui_receipteditdialog.h"

ReceiptEditDialog::ReceiptEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiptEditDialog)
{
    ui->setupUi(this);
    //ui->buttonBox->button(QDialogButtonBox::Apply)->
}

ReceiptEditDialog::~ReceiptEditDialog()
{
    delete ui;
}

void ReceiptEditDialog::setModel(ReceiptTableModel * const receiptModel, QSqlTableModel * const purchaseModel)
{
    ui->receiptEdit->setModel(receiptModel, purchaseModel);
}

void ReceiptEditDialog::setCurrentReceiptIndex(const QModelIndex &receiptIndex)
{
    ui->receiptEdit->setCurrentReceiptIndex(receiptIndex);
}

void ReceiptEditDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    auto role = ui->buttonBox->buttonRole(button);
    if(role == QDialogButtonBox::ApplyRole || role == QDialogButtonBox::AcceptRole)
    {
        ui->receiptEdit->submit();
    }
    else
    {
        ui->receiptEdit->revert();
    }
}

