#include "database.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>


const QString Database::connectionName = "default";
const QString Database::dbName = "record.db";

const QString Database::ReceiptTableName = "Receipt";
const QString Database::ReceiptTableDateTimeColumnName = "DateTime";

Database::Database(QObject *parent)
    : QObject{parent}
{

}

void Database::openDatabase()
{
    //QSqlDatabase::database(connectionName, false).close();
    //QSqlDatabase::removeDatabase(connectionName);
//    if(QSqlDatabase::database(connectionName, false).isOpen())
//    {
//        qWarning() << "db is alredy open.";
//        return;
//    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qWarning() << db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(connectionName);
    }

    //QSqlDatabase db = QSqlDatabase::database("Memo");
    QSqlQuery query(db);
    query.exec("DROP TABLE Receipt");
    query.exec("DROP TABLE Purchase");

    query.exec(tr("CREATE TABLE ") + Database::ReceiptTableName + tr("(Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Store INTEGER, DateTime INTEGER, PaymentMethod INTEGER, CurrencyCode INTEGER)"));
    query.exec(tr("INSERT INTO Receipt (Id, Store, DateTime, PaymentMethod, CurrencyCode) VALUES (1001, 1, 1300020000, 2, 392)"));
    query.exec(tr("INSERT INTO Receipt (Id, Store, DateTime, PaymentMethod, CurrencyCode) VALUES (1002, 32, 1661251320, 1, 392)"));

    query.exec(tr("CREATE TABLE Purchase (ReceiptId INTEGER, Id INTEGER, Description TEXT, UnitPrice REAL, Count INTEGER, TaxRate REAL, TaxExcluded BOOL, Usage INTEGER, PRIMARY KEY(ReceiptId, Id))"));
    query.exec(tr("INSERT INTO  Purchase (ReceiptId, Id, Description, UnitPrice, Count, TaxRate, TaxExcluded, Usage) VALUES (1001, 1, 'プレートWN6001W', 85, 1, 0.08, 0, 1)"));
    query.exec(tr("INSERT INTO  Purchase (ReceiptId, Id, Description, UnitPrice, Count, TaxRate, TaxExcluded, Usage) VALUES (1002, 1, 'イワフネコシヒカリ5KG', 2280, 1, 0.08, 1, 2)"));
    query.exec(tr("INSERT INTO  Purchase (ReceiptId, Id, Description, UnitPrice, Count, TaxRate, TaxExcluded, Usage) VALUES (1002, 2, 'コツブミニナツトウ', 69, 1, 0.08, 1, 2)"));
    query.exec(tr("INSERT INTO  Purchase (ReceiptId, Id, Description, UnitPrice, Count, TaxRate, TaxExcluded, Usage) VALUES (1002, 3, 'シンシユウソバ', 198, 1, 0.08, 1, 2)"));
    query.exec(tr("INSERT INTO  Purchase (ReceiptId, Id, Description, UnitPrice, Count, TaxRate, TaxExcluded, Usage) VALUES (1002, 4, 'シヨクセレウドン480', 198, 1, 0.08, 1, 2)"));

    query.exec(tr("CREATE TABLE CurrencyCode (Code INTEGER PRIMARY KEY AUTOINCREMENT, Symbol TEXT, Description TEXT)"));
    query.exec(tr("INSERT INTO  CurrencyCode VALUES (123, 'XXX', 'hoge')"));
    query.exec(tr("INSERT INTO  CurrencyCode VALUES (392, 'JPY', 'Japanese Yen')"));
    query.exec(tr("INSERT INTO  CurrencyCode VALUES (444, 'YYY', 'fuga')"));

    query.exec(tr("CREATE TABLE PaymentMethod (Id INTEGER PRIMARY KEY AUTOINCREMENT, Description TEXT, IsCredit BOOL)"));
    query.exec(tr("INSERT INTO  PaymentMethod VALUES (1, 'SMBC VISAデビット（末尾7652）', FALSE)"));
    query.exec(tr("INSERT INTO  PaymentMethod VALUES (2, 'SMBC VISAデビット（末尾7652） iD', FALSE)"));

    //    QSqlQuery q("", db);
//    //q.exec("drop table Movies");
//    //q.exec("drop table Names");
//    q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
//    q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
//    q.exec("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
//    q.exec("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
//    q.exec("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
//    q.exec("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
//    q.exec("create table Names (id integer primary key, FirstName varchar, LastName varchar, City varchar)");
//    q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
//    q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
//    q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
//    q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
//    q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");

    //db.close();
}


