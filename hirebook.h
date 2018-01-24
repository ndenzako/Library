#ifndef HIREBOOK_H
#define HIREBOOK_H
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
class QCheckBox;
QT_END_NAMESPACE


class hireBook : public QDialog
{
Q_OBJECT
public:
hireBook(QWidget *parent = 0);
void init();
void initWidget();
int getBookQuantity(const QString);
bool getService();
int getNumeroExemplaire();
QString getDate();
QString getNomEmprunteur();
QString getPrenomEmprunteur();
int findLastIndex();
QString getNuminv(const QLineEdit*);
int getDepartment();
//QString getBookTitle();
void resetFields();


public slots:
void selectButtonSlot();
void selectNewButton();
void showSaveButton();
void bookIdValidation();
//void activateMoreButton();
void activateGroupBox();
void enableNumExemplaireSlot();
void searchBook();
void saveHireBookData();


private:
QGroupBox *hireBookGroupBox;
QGroupBox *bringbackBookGroupBox;
QGroupBox *facultyGroupBox;
QGroupBox *marksGroupBox;

QGridLayout *personalIdGridlayout;
QGridLayout *facultyGridlayout;
QGridLayout *marksGridlayout1;
QGridLayout *marksGridlayout2;
QGridLayout *bringbackBookGridlayout;

QLabel *labelName;
//QLabel *postNameLabel;
QLabel *studentIdLabel;
QLabel *facultyLabel;
QLabel *departmentLabel;
QLabel *classLabel;
QLabel *yearLabel;
QLabel *departmentMLabel;
QLabel *marksLabel;
//QLabel *hireBookLabel;
QLabel *numInventaireLabel;
QLabel *nomEmprunteurLabel;


QLineEdit *nomEmprunteurLineEdit;
QLineEdit *prenomEmprunteur;
//QLineEdit *nomAuteurLineEdit;
QLineEdit *bookIdLineEdit;
QLineEdit *searchLineEdit;
QLineEdit *marksLineEdit;
QLineEdit *numInventaireLineEdit;


QComboBox *bookTitleCombo;
QComboBox *departmentComboBox;
QComboBox *actionComboBox;
QComboBox *searchComboBox;
QComboBox *nomEmprunteurComboBox;


QDateEdit *dateEdit;

QPushButton *okPushButtonRecord;
QPushButton *morePushButton;
QPushButton *selectPushButton;
QPushButton *newSelectionPushButton;
QPushButton *savePushButton;
QPushButton *closePushButton;


QVBoxLayout *personalIdVBox;
QVBoxLayout *marksVBox;
QVBoxLayout *mainVBoxLayout;


QHBoxLayout *closeHBoxLayout;



QSpinBox *numExemplaireSpinBox;

QCheckBox *hireBookCheckBox;

bool status;
static int lastIndex;




};
#endif //HIREBOOK_H
