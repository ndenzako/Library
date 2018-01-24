#include"searchbook.h" 
#include<QGroupBox>
#include<QGridLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QComboBox>
#include<QStringList>
searchDialog::searchDialog(QWidget *parent)
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

void searchDialog::init()
{
setFixedSize(500,200);
setWindowTitle(tr("Chercher un livre"));
searchGroupBox = new QGroupBox;
searchGroupBox->setTitle(tr("Mode de recheche"));

//searchLabel = new QLabel(tr("Chercher"));
bookTitleLabel = new QLabel(tr("Titre du livre"));

//cancelPushButton = new QPushButton(tr("Annuler"));
searchPushButton = new QPushButton(tr("Chercher"));
okPushButton = new QPushButton(tr("Quitter"));

searchLineEdit = new QLineEdit;

searchGridLayout = new QGridLayout;

okHBoxLayout = new QHBoxLayout;

keywordLabel = new QLabel(tr("Recherche par"));
keywordComboBox = new QComboBox;
bookTitleComboBox = new QComboBox;
QStringList keywordList;
keywordList<<"Mots clés"<<"Numéro inventaire";
keywordComboBox->addItems(keywordList);
mainVBoxLayout = new QVBoxLayout;

searchGridLayout->addWidget(keywordLabel,0,0);
searchGridLayout->addWidget(keywordComboBox,0,1,1,2);

//searchGridLayout->addWidget(searchLabel,1,0);
searchGridLayout->addWidget(searchLineEdit,1,1,1,2);
searchGridLayout->addWidget(searchPushButton,1,3);

searchGridLayout->addWidget(bookTitleLabel,2,0);
searchGridLayout->addWidget(bookTitleComboBox,2,1,1,2);

searchGroupBox->setLayout(searchGridLayout);

okHBoxLayout->addStretch();
//okHBoxLayout->addWidget(cancelPushButton);
//okHBoxLayout->addWidget(searchPushButton);
okHBoxLayout->addWidget(okPushButton);

mainVBoxLayout->addWidget(searchGroupBox);
mainVBoxLayout->addLayout(okHBoxLayout);

setLayout(mainVBoxLayout);
}


void searchDialog::connectSlots()
{
connect(okPushButton,SIGNAL(clicked()),this,SLOT(accept()));
connect(searchPushButton,SIGNAL(clicked()),this,SLOT(searchSlot()));

}

void searchDialog::searchSlot()
{
QString strDepartment = searchLineEdit->text();
if(!strDepartment.isEmpty())
{
QString strDepartmentQuery = QString("INSERT INTO department(departmentName) VALUES(%0%1%2)").arg("'").arg(strDepartment).arg("'");
QSqlQueryModel departQuery;
departQuery.setQuery(strDepartmentQuery);
searchLineEdit->clear();
}
else
{
QMessageBox::information(this,tr("Information"),tr("<h3>Entrer les mots de recherche ou le numéro d'inventaire.</h3>"));
}
}
