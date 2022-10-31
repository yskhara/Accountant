#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    void openDatabase();


    static const QString ReceiptTableName;
    static const QString ReceiptTableDateTimeColumnName;
    static const QString ReceiptTableStoreColumnName;


public slots:


signals:

private:

    static const QString connectionName;
    static const QString dbName;

    bool isOpen();
};

#endif // DATABASE_H
