#ifndef ADMINI_H
#define ADNIN_H
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
QT_END_NAMESPACE
class adminDialog:public QDialog
{
Q_OBJECT
public:
adminDialog(QWidget *parent= 0);
void init();
void connectSlots();

public slots:
void addDepartSlot();
private:
QGroupBox *addDepartmentGroupBox;

QLabel *addDepartmentLabel;

QPushButton *cancelPushButton;
QPushButton *savePushButton;
QPushButton *okPushButton;

QLineEdit *addDepartmentLineEdit;

QGridLayout *departmentGridLayout;

QHBoxLayout *okHBoxLayout;

QVBoxLayout *mainVBoxLayout;
};
#endif //ADMINI_H
