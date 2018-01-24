#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H
#include<QDialog>
QT_BEGIN_NAMESPACE
class QGroupBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QSqlQueryModel;
class QMessageBox;
class QComboBox;
class QStringList;
QT_END_NAMESPACE
class searchDialog:public QDialog
{
Q_OBJECT
public:
searchDialog(QWidget *parent= 0);
void init();
void connectSlots();

public slots:
void searchSlot();
private:
QGroupBox *searchGroupBox;

QLabel *searchLabel;
QLabel *keywordLabel;
QLabel *bookTitleLabel;

//QPushButton *cancelPushButton;
QPushButton *searchPushButton;
QPushButton *okPushButton;

QLineEdit *searchLineEdit;

QGridLayout *searchGridLayout;

QHBoxLayout *okHBoxLayout;

QVBoxLayout *mainVBoxLayout;

QComboBox *keywordComboBox;
QComboBox *bookTitleComboBox;
};
#endif //SEARCHBOOK_H
