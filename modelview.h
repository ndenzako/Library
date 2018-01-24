#ifndef MODELBIEW_H
#define MODELBIEW_H
#include<QtGui>
#include<QDialog>
#include<QSqlRecord>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>

class QSqlTableModel;
class QTableView;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QSqlQuery;
class QString;

inline int generateId(const QString &table)
{
QSqlQuery query;
query.exec("SELECT MAX(id) FROM " + table);
int id = 0;
if (query.next())
id = query.value(0).toInt() + 1;
return id;
}

class ArtistForm : public QDialog
{
Q_OBJECT
public:
ArtistForm(const QString &name, QWidget *parent = 0);
private slots:
void addArtist();
void deleteArtist();
void beforeInsertArtist(QSqlRecord &record);
private:
enum {
Artist_Id = 0,
Artist_Name = 1,
Artist_Country = 2
};
QSqlTableModel *model;
QTableView *tableView;
QPushButton *addButton;
QPushButton *deleteButton;
QPushButton *closeButton;
QHBoxLayout *hBoxLayoutButton;
QVBoxLayout *vBoxlayout;
};

#endif//
