#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H
#include <QDialog>
//#include "ui_recordmarks.h"
class QPushButton;
class QGroupBox;
class QGridLayout;
class QSqlQueryModel;
class QDataWidgetMapper;
class QSqlRelationalDelegate;
class QSqlError;
class QSqlRecord;
class QSqlQuery;
class QMessageBox;
class QVBoxLayout;
class QComboBox;
class QLabel;
class QLineEdit;
//class QDateEdit;
class QHBoxLayout;


class historyDialog : public QDialog
{
Q_OBJECT
public:
historyDialog(QWidget *parent = 0);
void init();

void initWidget();



public slots:



void selectButtonSlot();
void selectNewButton();
void showSaveButton();

private:
QGroupBox *personalIdGroupBox;
QGroupBox *facultyGroupBox;
QGroupBox *marksGroupBox;
QGridLayout *personalIdGridlayout;
QGridLayout *facultyGridlayout;
QGridLayout *marksGridlayout1;
QGridLayout *marksGridlayout2;

QLabel *labelName;
QLabel *postNameLabel;
QLabel *studentIdLabel;
QLabel *facultyLabel;
QLabel *departmentLabel;
QLabel *classLabel;
//QLabel *yearLabel;
QLabel *departmentMLabel;
//QLabel *classMLabel;
//QLabel *courseMLabel;
//QLabel *studentIdLabel1;
//QLabel *searchLabel;
QLabel *marksLabel;

//QLineEdit *lineEditName;
QLineEdit *nomEmpreinteurLineEdit;
QLineEdit *prenomEmpreinteur;
QLineEdit *nomAuteurLineEdit;
QLineEdit *bookIdLineEdit;
//QLineEdit *studentIdRecordMarksLineEdit;
QLineEdit *searchLineEdit;
QLineEdit *marksLineEdit;


QComboBox *bookTitleCombo;
//QComboBox *facultyComboBox;
QComboBox *departmentComboBox;
//QComboBox *classComboBox;
QComboBox *actionComboBox;
//QComboBox *classRecordMarksComboBox;
//QComboBox *courseRecordMarksComboBox;
QComboBox *searchComboBox;


//QDateEdit *dateEdit;

QPushButton *viewPushButton;
QPushButton *morePushButton;
QPushButton *selectPushButton;
QPushButton *newSelectionPushButton;
//QPushButton *savePushButton;
QPushButton *closePushButton;


QVBoxLayout *personalIdVBox;
QVBoxLayout *marksVBox;
QVBoxLayout *mainVBoxLayout;


QHBoxLayout *closeHBoxLayout;

//QSqlQueryModel *queryModel; ////???????????????????????????????????????




bool status;




};
#endif //HISTORYDIALOG_H
