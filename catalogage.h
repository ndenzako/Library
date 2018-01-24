#ifndef CATALOGAGE_H
#define CATALOGAGE_H
#include <QDialog>
//#include "ui_recordmarks.h"
QT_BEGIN_NAMESPACE
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
class QDateEdit;
class QHBoxLayout;
class QSpinBox;
class QDebug;
class QCheckBox;
QT_END_NAMESPACE


class catalogageDialog : public QDialog
{
Q_OBJECT
public:
catalogageDialog(QWidget *parent = 0);
void init();
void getPersonalId();
void initWidget();
void getComment();
//void getCatalogueTable();
public slots:


//Slot to retrieve information for the dialogue and save them in the database.
void bookIdValidation();
void isbCkeckSlot();
void enableExemplaireSlot();
void activateSaveButton();
void enableCommentLineEditSlot();

private:
QGroupBox *personalIdGroupBox;
QGroupBox *facultyGroupBox;
QGroupBox *marksGroupBox;
QGridLayout *personalIdGridlayout;
QGridLayout *facultyGridlayout;
//QGridLayout *marksGridlayout1;
QGridLayout *marksGridlayout2;

QLabel *labelName;
QLabel *postNameLabel;
QLabel *studentIdLabel;
QLabel *localisationLabel;

//QLabel *classLabel;
//QLabel *yearLabel;
QLabel *departmentMLabel;
//QLabel *marksLabel;

//QLineEdit *nomEmpreinteurLineEdit;
//QLineEdit *prenomEmpreinteur;
QLineEdit *bookCoteLineEdit;
QLineEdit *numInventaireLineEdit;
QLineEdit *searchLineEdit;
QLineEdit *marksLineEdit;
QLineEdit *commentLineEdit;


QComboBox *bookTypeCombo;
QComboBox *actionComboBox;
QComboBox *searchComboBox;
QComboBox *bookLocalisationCombo;


QSpinBox *numberExemplaireSpinBox;


QDateEdit *dateEdit;

QPushButton *okPushButtonRecord;
//QPushButton *morePushButton;
QPushButton *selectPushButton;
QPushButton *newSelectionPushButton;
QPushButton *savePushButton;
QPushButton *closePushButton;


QVBoxLayout *personalIdVBox;
QVBoxLayout *marksVBox;
QVBoxLayout *mainVBoxLayout;


QHBoxLayout *closeHBoxLayout;

QCheckBox *exemplaireCheckBox;
QCheckBox *commentCheckBox;

//QSqlQueryModel *queryModel; ////???????????????????????????????????????



bool status;
bool isbCkeck;




};
#endif //CATALOGAGE_H
