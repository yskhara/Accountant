#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "database.h"
#include "receipteditdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void on_pushButtonAddReceiptEntry_clicked();

    void on_pushButtonUpdateReceiptEntry_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButtonRemoveReceiptEntry_clicked();

private:
    Ui::MainWindow *ui;

    Database *db;
    ReceiptEditDialog *receiptEditDialog = nullptr;
    //QDialog *receiptEditDialog = nullptr;
    //ReceiptEditWidget *receiptEditWidget = nullptr;
};
#endif // MAINWINDOW_H
