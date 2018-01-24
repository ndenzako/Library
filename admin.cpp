#include"admin.h" 
#include<QGroupBox>
#include<QGridLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSqlQueryModel>
#include<QMessageBox>
adminDialog::adminDialog(QWidget *parent)
:QDialog(parent)
{
init();
connectSlots();

this->setStyleSheet("QGroupBox"
    "{"
        "background-color:transparent;"
        "border-bottom-left-radius: 3px;"
        "border-bottom-right-radius: 3px;"
        "border: 3px solid #acacac;"
        "border-top: 3px solid #acacac none;"
        "margin-top: 15px;"
        "margin-left: 0px;"
    "}"
    "QGroupBox::title"
    "{"
        "subcontrol-origin: margin;"
        "background:url(:/assets/subWindowBackground);"
        "border-top-left-radius: 3px;"
        "border-top-right-radius: 3px;"
        "border: 3px solid #0b477b;"
        "border-bottom: none;"
        "background-color: qlineargradient(x1: 30, y1: 10, x2: 30, y2: 10,"
            "stop: 0 #005192, stop: 1 #002f60);"
        "padding: 2 2px;"
        "color: white;"
    "}");
    
}

void adminDialog::init()
{
setFixedSize(500,150);
setWindowTitle(tr("Ajout d'un département"));
addDepartmentGroupBox = new QGroupBox;
addDepartmentGroupBox->setTitle(tr("Ajout départment"));

addDepartmentLabel = new QLabel(tr("Département"));

cancelPushButton = new QPushButton(tr("Annuler"));
savePushButton = new QPushButton(tr("Ajouter"));
okPushButton = new QPushButton(tr("Quitter"));

addDepartmentLineEdit = new QLineEdit;

departmentGridLayout = new QGridLayout;

okHBoxLayout = new QHBoxLayout;

mainVBoxLayout = new QVBoxLayout;
departmentGridLayout->addWidget(addDepartmentLabel,0,0);
departmentGridLayout->addWidget(addDepartmentLineEdit,0,1,1,2);

addDepartmentGroupBox->setLayout(departmentGridLayout);

okHBoxLayout->addStretch();
okHBoxLayout->addWidget(cancelPushButton);
okHBoxLayout->addWidget(savePushButton);
okHBoxLayout->addWidget(okPushButton);

mainVBoxLayout->addWidget(addDepartmentGroupBox);
mainVBoxLayout->addLayout(okHBoxLayout);

setLayout(mainVBoxLayout);
}


void adminDialog::connectSlots()
{
connect(okPushButton,SIGNAL(clicked()),this,SLOT(accept()));
connect(savePushButton,SIGNAL(clicked()),this,SLOT(addDepartSlot()));

}

void adminDialog::addDepartSlot()
{
QString strDepartment = addDepartmentLineEdit->text();
if(!strDepartment.isEmpty())
{
QString strDepartmentQuery = QString("INSERT INTO department(departmentName) VALUES(%0%1%2)").arg("'").arg(strDepartment).arg("'");
QSqlQueryModel departQuery;
departQuery.setQuery(strDepartmentQuery);
addDepartmentLineEdit->clear();
}
else
{
QMessageBox::information(this,tr("Information"),tr("No empty string for department allowed"));
}
}
