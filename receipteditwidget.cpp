#include "receipteditwidget.h"
#include "ui_receipteditwidget.h"

#include "ReceiptTableDelegate.h"

#include <QSqlError>
//#include <QSqlTableModel>

ReceiptEditWidget::ReceiptEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiptEditWidget),
    mapper(new QDataWidgetMapper(this))
{
    ui->setupUi(this);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

ReceiptEditWidget::~ReceiptEditWidget()
{
    delete ui;
}

void ReceiptEditWidget::setModel(ReceiptTableModel * const receiptModel, QSqlTableModel * const purchaseModel) {
    //this->model = model;

    int paymentMethodIndex = receiptModel->fieldIndex("Description");
    int idIndex = receiptModel->fieldIndex("Id");
    int storeIndex = receiptModel->fieldIndex("Store");
    int dateTimeIndex = receiptModel->fieldIndex("DateTime");

    //ui->dateTimeEdit->setDateTime(model->data())
    ui->paymentMethodComboBox->setModel(receiptModel->relationModel(paymentMethodIndex));
    ui->paymentMethodComboBox->setModelColumn(
        receiptModel->relationModel(paymentMethodIndex)->fieldIndex("Description"));

    //QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(receiptModel);
    //mapper->addMapping(ui->receiptIdEdit, idIndex);
    mapper->addMapping(ui->dateTimeEdit, dateTimeIndex);
    mapper->addMapping(ui->storeEdit, storeIndex);
    mapper->addMapping(ui->paymentMethodComboBox, paymentMethodIndex);
    mapper->setItemDelegate(new ReceiptTableDelegate(mapper));
    //mapper->addMapping(ui.genreEdit, genreIdx);
    //mapper->addMapping(ui.ratingEdit, model->fieldIndex("rating"));

    ui->tableView->setModel(purchaseModel);
    ui->tableView->setColumnHidden(0, true);

    //connect(ui->tableView->selectionModel(),
    //        &QItemSelectionModel::currentRowChanged,
    //        mapper,
    //        &QDataWidgetMapper::setCurrentModelIndex
    //        );
}

void ReceiptEditWidget::setCurrentReceiptIndex(const QModelIndex &receiptIndex)
{
    mapper->setCurrentModelIndex(receiptIndex);
    bool ok = false;
    qlonglong id = receiptIndex.siblingAtColumn(0).data().toULongLong(&ok);
    ui->receiptIdEdit->setText((id == 0 || !ok) ? "" : QString::number(id));
    auto model = qobject_cast<QSqlTableModel *>(ui->tableView->model());
    if(ok)// && id != 0)
    {
        model->setFilter(tr("receiptId='") + QString::number(id) + tr("'"));
    }
    else
    {
        qWarning() << "Receipt ID is ill-formed.";
    }
    model->select();
    ui->tableView->resizeColumnsToContents();
}

void ReceiptEditWidget::submit(void)
{
    bool mapperSubmitResult = mapper->submit();
    qInfo () << "mapper->submit() called: " << mapperSubmitResult;
    bool modelSubmitResult = ((QSqlRelationalTableModel * const)mapper->model())->submitAll();
    qInfo () << "model->submit() called: " << modelSubmitResult;
    if(!modelSubmitResult)
    {
        qInfo () << ((QSqlRelationalTableModel * const)mapper->model())->lastError().text();
    }
    //bool modelSelectResult = ((QSqlRelationalTableModel * const)mapper->model())->select();
    //qInfo () << "model->select() called: " << modelSubmitResult;
    //if(!modelSelectResult)
    //{
    //    qInfo () << ((QSqlRelationalTableModel * const)mapper->model())->lastError().text();
    //}
}

void ReceiptEditWidget::revert(void)
{
    mapper->revert();
    ((QSqlRelationalTableModel * const)mapper->model())->revertAll();
}

