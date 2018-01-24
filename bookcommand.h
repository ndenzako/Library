#ifndef BOOKCOMMAND_H
#define BOOKCOMMAND_H
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
class QCheckBox;
class QCheckBox;
class QSpinBox;
QT_END_NAMESPACE


class bookCommand : public QDialog
{
Q_OBJECT
public:
bookCommand(QWidget *parent = 0);
void init();
void getPersonalId();
void initWidget();
QString getNumInv();
void getIsbn();
bool bookIdValidation(QString bookid);
void clearTitle();
void getSubTitle();
void getPrice();
void getQuantity();
void getPubYear();

public slots:


void selectButtonSlot();
void selectNewButton();
void showSaveButton();
void enableSubTitleLineEdit();
void enablePrixLineEdit();
void enableQuantitySpinBox();
void getTitle();
bool modeAcquisistion();
void enableDateEdit();
void enableBookIdLineEditSlot();



//void dateSlot();

//void bookIdValidation();

private:
QGroupBox *titleGroupBox;
QGroupBox *subTitleGroupBox;
//QGroupBox *marksGroupBox;

QGridLayout *personalIdGridlayout;
QGridLayout *facultyGridlayout;
QGridLayout *marksGridlayout1;
QGridLayout *marksGridlayout2;
QGridLayout *subTitleGridLayout;

QLabel *labelName;
QLabel *postNameLabel;
//QLabel *bookIdLabel;
QLabel *facultyLabel;
QLabel *departmentLabel;
QLabel *classLabel;
//QLabel *yearLabel;

QLabel *marksLabel;
QLabel *modeAcquisitionLabel;
QLabel *numInventaireLabel;



//QLineEdit *nomEmpreinteurLineEdit;
//QLineEdit *prenomEmpreinteur;
QLineEdit *bookAuthorLineEdit;
QLineEdit *bookIdLineEdit;
//QLineEdit *searchLineEdit;
//QLineEdit *marksLineEdit;
QLineEdit *bookTitleLineEdit;
QLineEdit *subTitleLineEdit;
QLineEdit *prixLineEdit;
QLineEdit *numInventaireLineEdit;


//QComboBox *bookTitleCombo;
QComboBox *modeAcquisitionComboBox;//>???????????????????
QComboBox *actionComboBox;
//QComboBox *searchComboBox;


QSpinBox *quantitySpinBox;


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
//QHBoxLayout *subTitleRadioHBoxLayout;

QSqlQueryModel *queryModel; ////???????????????????????????????????????

QCheckBox *subTitleCheckBox;
QCheckBox *prixCheckBox;//??????????????????????????
QCheckBox *quantityCheckBox;
QCheckBox *yearCheckBox;
QCheckBox *bookIdCheckBox;

bool status;




};
#endif //BOOKCOMMAND_H
