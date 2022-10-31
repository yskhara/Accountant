#ifndef RECEIPTTABLEMODEL_H
#define RECEIPTTABLEMODEL_H

#include <QVariant>
#include <QDateTime>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

class ReceiptModel
{
private:
    qulonglong id;
    QDateTime dateTime;



public:
    qulonglong Id(void) {
        return id;
    }

};

class ReceiptTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit ReceiptTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase()):QSqlRelationalTableModel(parent, db)
    {}

    virtual ~ReceiptTableModel()
    {}

    //QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role) const override
    {
        //Q_D(const QSqlRelationalTableModel);

        if (role == Qt::DisplayRole && index.isValid() && index.column() == 2){
                //>= 0 && index.column() < d->relations.size() &&
                //d->relations.value(index.column()).isValid()) {
            //QRelation &relation = d->relations[index.column()];
            //if (!relation.isDictionaryInitialized())
            //    relation.populateDictionary();

            bool ok = false;
            qlonglong time = QSqlTableModel::data(index, role).toLongLong(&ok);
            if(ok)
                return QVariant(QDateTime::fromSecsSinceEpoch(time));

            //only perform a dictionary lookup for the display value
            //when the value at index has been changed or added.
            //At an unmodified index, the underlying model will
            //already have the correct display value.
//            if (d->strategy != OnFieldChange) {
//                const QSqlTableModelPrivate::ModifiedRow row = d->cache.value(index.row());
//                if (row.op() != QSqlTableModelPrivate::None && row.rec().isGenerated(index.column())) {
//                    if (d->strategy == OnManualSubmit || row.op() != QSqlTableModelPrivate::Delete) {
//                        QVariant v = row.rec().value(index.column());
//                        if (v.isValid())
//                            return relation.dictionary[v.toString()];
//                    }
//                }
//            }
        }
        return QSqlRelationalTableModel::data(index, role);
    }

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole && orientation == Qt::Vertical)
        {
            bool ok = false;
            qlonglong id = this->record(section).value("Id").toULongLong(&ok);
            return (id == 0 || !ok) ? "" : QString::number(id);
        }

        return QSqlRelationalTableModel::headerData(section, orientation, role);
    }

    static bool GetReceiptModel(const QModelIndex &index, ReceiptModel * const model) {
    }

};

#endif // RECEIPTTABLEMODEL_H
