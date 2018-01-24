#include<QtGui>
#include"history.h"
#include<QPushButton>
#include<QSqlQueryModel>
#include<QVBoxLayout>
#include<QSqlRelationalDelegate>
#include<QSqlError>
#include<QSqlQuery>
#include<QMessageBox>
#include<QComboBox>
#include<QLabel>
#include<QLineEdit>
#include<QGroupBox>
#include<QHBoxLayout>

#include<QSqlRecord>

historyDialog::historyDialog(QWidget *parent)
: QDialog(parent)
{
	setWindowTitle(tr("Library history"));
	initWidget();
	init();
	
	personalIdGroupBox->hide();
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	morePushButton->setCheckable(true);
	status = true;
	connect(morePushButton, SIGNAL(toggled(bool)), this, SLOT(showSaveButton()));
	connect(morePushButton, SIGNAL(toggled(bool)), personalIdGroupBox, SLOT(setVisible(bool)));
	
	connect(selectPushButton, SIGNAL(clicked()), this, SLOT(selectButtonSlot()));
	connect(newSelectionPushButton, SIGNAL(clicked()), this, SLOT(selectNewButton()));
	connect(closePushButton,SIGNAL(clicked()),this,SLOT(accept()));
	

	
	
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
    
bookIdLineEdit->setStyleSheet("QLineEdit"
    "{"
        "background-color:#FFFF99;"
        "border-bottom-left-radius: 8px;"
        "border-top-right-radius: 8px;"
        "border: 3px solid #acacac;"
        "border-top: 3px solid #acacac none;"
    "}"
    );
}

void historyDialog::init()
{

QString strFacultyQuery = "SELECT DISTINCT facultyname FROM faculty";
QString strDepartmentQuery = "SELECT DISTINCT departmentname FROM department";
QString strClassQuery = "SELECT DISTINCT className FROM classtable";

QSqlQueryModel modelFaculty;
modelFaculty.setQuery(strFacultyQuery);

QStringList strFacultyList;
for(int i = 0; i < modelFaculty.rowCount(); ++i)
{
	
	QString strFac = modelFaculty.record(i).value("facultyname").toString();
	strFacultyList.append(strFac);
}
QStringList actionList;
actionList<<"Selection une action"<<"Disponible"<<"En location";

actionComboBox->addItems(actionList);

QSqlQueryModel modelClass;
modelClass.setQuery(strClassQuery);

for(int i = 0; i < modelClass.rowCount(); ++i)
{
	QStringList strClassList;
	QString strClass = modelClass.record(i).value("classname").toString();
	strClassList.append(strClass);
	
}
    newSelectionPushButton->setEnabled(false);
    QStringList strCourseList;
}





void historyDialog::selectButtonSlot()
{

if(status)
{
actionComboBox->setEnabled(false);
selectPushButton->setEnabled(false);
newSelectionPushButton->setEnabled(true);
status = false;
}
else
{
actionComboBox->setEnabled(true);
selectPushButton->setEnabled(true);
}

}

void historyDialog::selectNewButton()
{
if(!status)
{
actionComboBox->setEnabled(true);
selectPushButton->setEnabled(true);
newSelectionPushButton->setEnabled(false);
status = true;
}
}
//==================================================================================
void historyDialog::initWidget()
{
personalIdGroupBox = new QGroupBox;
personalIdGroupBox->setTitle(tr("Enregistrer les donnees"));
facultyGroupBox = new QGroupBox;
marksGroupBox = new QGroupBox;
marksGroupBox->setTitle(tr("Disponibilite en stock"));

personalIdGridlayout = new QGridLayout;
facultyGridlayout = new QGridLayout;
marksGridlayout1 = new QGridLayout;
marksGridlayout2 = new QGridLayout;

labelName = new QLabel(tr("Titre du livre"));
postNameLabel = new QLabel(tr("Nom de l'auteur"));
studentIdLabel = new QLabel(tr("Identite du livre"));
facultyLabel = new QLabel(tr("Nom de l'empreinteur"));
departmentLabel = new QLabel(tr("Departement"));
classLabel = new QLabel(tr("Prenom de l'empreinteur"));


departmentMLabel = new QLabel(tr("Action"));
bookTitleCombo = new QComboBox;
bookTitleCombo->setFixedSize(350,30);
nomAuteurLineEdit = new QLineEdit;
nomAuteurLineEdit->setFixedSize(350,30);
bookIdLineEdit = new QLineEdit;
bookIdLineEdit->setFixedSize(350,30);
nomEmpreinteurLineEdit = new QLineEdit;
nomEmpreinteurLineEdit->setFixedSize(300,30);
departmentComboBox = new QComboBox;
prenomEmpreinteur = new QLineEdit;
prenomEmpreinteur->setFixedSize(300,30);
actionComboBox = new QComboBox;
viewPushButton = new QPushButton(tr("View"));
viewPushButton->setFixedSize(60,30);
morePushButton = new QPushButton(tr("&More>>"));
morePushButton->setFixedSize(60,30);
selectPushButton = new QPushButton(tr("Selection"));

newSelectionPushButton = new QPushButton(tr("Nouvelle selection"));
closePushButton = new QPushButton(tr("&Ok"));
personalIdGridlayout->addWidget(labelName,0,0);
personalIdGridlayout->addWidget(bookTitleCombo,0,1,1,2);

personalIdGridlayout->addWidget(postNameLabel,1,0);
personalIdGridlayout->addWidget(nomAuteurLineEdit,1,1,1,2);

personalIdGridlayout->addWidget(studentIdLabel,2,0);
personalIdGridlayout->addWidget(bookIdLineEdit,2,1,1,2);
//==========
//==========Grid
facultyGridlayout->addWidget(facultyLabel,0,0);
facultyGridlayout->addWidget(nomEmpreinteurLineEdit,0,1,1,2);

facultyGridlayout->addWidget(classLabel,1,0);
facultyGridlayout->addWidget(prenomEmpreinteur,1,1,1,2);

facultyGridlayout->addWidget(departmentLabel,2,0);
facultyGridlayout->addWidget(departmentComboBox,2,1,1,2);

marksGridlayout1->addWidget(departmentMLabel,0,0);
marksGridlayout1->addWidget(actionComboBox,0,1,1,5);

marksGridlayout1->addWidget(selectPushButton,3,4);
marksGridlayout1->addWidget(newSelectionPushButton,3,5);

closeHBoxLayout = new QHBoxLayout;
closeHBoxLayout->addStretch();
closeHBoxLayout->addWidget(morePushButton);
viewPushButton->hide();
closeHBoxLayout->addWidget(viewPushButton);
closeHBoxLayout->addWidget(closePushButton);
personalIdVBox = new QVBoxLayout;
personalIdVBox->addLayout(personalIdGridlayout);
personalIdVBox->addLayout(facultyGridlayout);

personalIdGroupBox->setLayout(personalIdVBox);

marksVBox = new QVBoxLayout;
marksVBox->addLayout(marksGridlayout1);
marksVBox->addLayout(marksGridlayout2);
marksGroupBox->setLayout(marksVBox);

mainVBoxLayout = new QVBoxLayout;

mainVBoxLayout->addWidget(marksGroupBox);
mainVBoxLayout->addWidget(personalIdGroupBox);
mainVBoxLayout->addLayout(closeHBoxLayout);
setLayout(mainVBoxLayout);
}

void historyDialog::showSaveButton()
{
if(morePushButton->isChecked())
{
viewPushButton->show();
}
else
{
viewPushButton->hide();
}

}








