#include"connexion.h"

bool createConnexion(QString &databasename)
{
QSqlDatabase testDb = QSqlDatabase::addDatabase("QSQLITE");
testDb.setDatabaseName(databasename);
//testDb.setHostName("127.0.0.1");
testDb.setUserName("username");
testDb.setPassword("pwd");

if (!testDb.open())
{
QMessageBox::critical(0, QObject::tr("Database Error"),
testDb.lastError().text());
}


if(!testDb.open())
	{
	qCritical("Cannot open database: %s (%s)",
testDb.lastError().text().toLatin1().data(),
qt_error_string().toLocal8Bit().data());
return false;
		}
		return true;
}
