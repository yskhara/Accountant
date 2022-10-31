#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include "ReceiptTableDelegate.h"
#include "ReceiptTableModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db()
{
    ui->setupUi(this);

    db->openDatabase();

    //QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    ReceiptTableModel *model = new ReceiptTableModel(this);
    //QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    //QSqlTableModel *model = new QSqlTableModel(ui->tableView);
    model->setTable("Receipt");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    auto paymentMethodIndex = model->fieldIndex("PaymentMethod");
    auto currencyCodeIndex = model->fieldIndex("CurrencyCode");

    model->setRelation(paymentMethodIndex, QSqlRelation("PaymentMethod", "Id", "Description"));
    model->setRelation(currencyCodeIndex, QSqlRelation("CurrencyCode", "Code", "Symbol"));
    model->setHeaderData(paymentMethodIndex, Qt::Horizontal, tr("Payment method"));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new ReceiptTableDelegate(ui->tableView));
    ui->tableView->resizeColumnsToContents();
    //ui->tableView->resizeRowsToContents();
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddReceiptEntry_clicked()
{
    ReceiptTableModel * const model = ((ReceiptTableModel *)ui->tableView->model());
    auto record = model->record();
    //record.setValue(tr("Id"), 1020);
    //record.remove(record.indexOf("Id"));
    record.setGenerated("Id", false);
    record.setValue(tr("Store"), 0);
    record.setValue(tr("PaymentMethod"), 0);
    record.setValue(tr("Symbol"), 392);
    record.setValue(tr("DateTime"), QDateTime::currentDateTimeUtc().toSecsSinceEpoch());
    model->insertRecord(-1, record);
    ui->tableView->selectRow(model->rowCount() - 1);
    on_tableView_doubleClicked(ui->tableView->selectionModel()->currentIndex());
}

void MainWindow::on_pushButtonUpdateReceiptEntry_clicked()
{
    //ReceiptTableModel * const model = ((ReceiptTableModel *)ui->tableView->model());
    //model->select();
}

void MainWindow::on_pushButtonRemoveReceiptEntry_clicked()
{
    if(ui->tableView->selectionModel()->hasSelection())
    {
        QMessageBox msgBox(QMessageBox::Icon::Warning, "Warning", "Are you sure you want to remove this item? \nThis cannot be undone.", QMessageBox::Yes | QMessageBox::No, this);
        //msgBox.setText("Are you sure you want to remove this item?");
        //msgBox.setInformativeText("This cannot be undone.");
        //msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        if(msgBox.exec() == QMessageBox::Yes)
        {
            QSqlRelationalTableModel * model = qobject_cast<QSqlRelationalTableModel *>(ui->tableView->model());
            model->removeRow(ui->tableView->selectionModel()->currentIndex().row());
            model->submitAll();
        }
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(receiptEditDialog == nullptr)
    {
        auto purchaseModel = new QSqlTableModel(this);
        //QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        //QSqlTableModel *model = new QSqlTableModel(ui->tableView);
        purchaseModel->setTable("Purchase");
        purchaseModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        receiptEditDialog = new ReceiptEditDialog(this);
        receiptEditDialog->setModel((ReceiptTableModel *)ui->tableView->model(), purchaseModel);
    }

    receiptEditDialog->setCurrentReceiptIndex(index);
    receiptEditDialog->show();
}

