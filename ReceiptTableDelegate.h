#ifndef RECEIPTTABLEDELEGATE_H
#define RECEIPTTABLEDELEGATE_H
#include "database.h"
#include "ReceiptTableModel.h"
#include <QSqlRelationalDelegate>
#include <QDateTimeEdit>

class ReceiptTableDelegate : public QSqlRelationalDelegate
{
    static int fieldIndex(const QSqlTableModel *const model,
                          const QSqlDriver *const driver,
                          const QString &fieldName)
    {
        const QString stripped = driver->isIdentifierEscaped(fieldName, QSqlDriver::FieldName)
                ? driver->stripDelimiters(fieldName, QSqlDriver::FieldName)
                : fieldName;
        return model->fieldIndex(stripped);
    }

public:

    explicit ReceiptTableDelegate(QObject *aParent = nullptr)
        : QSqlRelationalDelegate(aParent)
    {}

    ~ReceiptTableDelegate()
    {}

    QString displayText(const QVariant &value, const QLocale &locale) const override
    {
        if (value.metaType() == QMetaType::fromType<QDateTime>())
        {
            qInfo("displayText() called for QDateTime.");
            return value.toDateTime().toString(locale.dateTimeFormat());
        }

        qInfo() << "displayText() called for something else: " << value.metaType().name();
        qInfo() << "    data: " << value.toString();
        return QSqlRelationalDelegate::displayText(value, locale);
    }

    QWidget *createEditor(QWidget *aParent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        qInfo("createEditor() called.");

        const QSqlTableModel *tabModel = qobject_cast<const QSqlTableModel *>(index.model());

        qInfo(tabModel->headerData(index.column(), Qt::Horizontal).toString().toLatin1());
        return nullptr;

        if (tabModel != nullptr && tabModel->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString().compare(Database::ReceiptTableDateTimeColumnName) == 0) {
            QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(aParent);
            dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
            dateTimeEdit->installEventFilter(const_cast<ReceiptTableDelegate *>(this));
            return dateTimeEdit;
        }

        return QSqlRelationalDelegate::createEditor(aParent, option, index);
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        if (!index.isValid())
            return;

        if (qobject_cast<QDateTimeEdit *>(editor)) {
            QVariant v = index.data(Qt::EditRole);
            const QByteArray n = editor->metaObject()->userProperty().name();
            if (!n.isEmpty()) {
                if (v.metaType() == QMetaType::fromType<qlonglong>()) {
                    qobject_cast<QDateTimeEdit *>(editor)->setDateTime(QDateTime::fromSecsSinceEpoch(v.toLongLong()));
                    return;
                }
            }
        }
        QSqlRelationalDelegate::setEditorData(editor, index);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        if (!index.isValid())
            return;

        ReceiptTableModel *receiptModel = qobject_cast<ReceiptTableModel *>(model);
        QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit *>(editor);
        if(!receiptModel || !dateTimeEdit)
        {
            return QSqlRelationalDelegate::setModelData(editor, model, index);
        }
        qInfo() << "setModelData() for QDateTimeEdit was called.";
        receiptModel->setData(index, dateTimeEdit->dateTime().toString(tr("yyyy-MMM-dd HH:mm:ss")), Qt::DisplayRole);
        receiptModel->setData(index, dateTimeEdit->dateTime().toSecsSinceEpoch(), Qt::EditRole);
    }

};



#endif // RECEIPTTABLEDELEGATE_H
