#include<QtGui>
#include"bookcommand.h"
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
#include<QDateEdit>
#include<QGroupBox>
#include<QHBoxLayout>
#include<QCheckBox>

#include<QSpinBox>

#include<QSqlRecord>

bookCommand::bookCommand(QWidget *parent)
: QDialog(parent)
{
	queryModel = new QSqlQueryModel(this);
	setWindowTitle(tr("Commande and acquisition"));
	initWidget();
	init();
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	morePushButton->setCheckable(true);
	status = true;
	connect(morePushButton, SIGNAL(toggled(bool)), this, SLOT(showSaveButton()));
	connect(morePushButton, SIGNAL(toggled(bool)), titleGroupBox, SLOT(setVisible(bool)));

	connect(selectPushButton, SIGNAL(clicked()), this, SLOT(selectButtonSlot()));
	connect(newSelectionPushButton, SIGNAL(clicked()), this, SLOT(selectNewButton()));
	connect(closePushButton,SIGNAL(clicked()),this,SLOT(accept()));
	//connect(savePushButton,SIGNAL(clicked()),this,SLOT(bookIdValidation()));
	connect(subTitleCheckBox,SIGNAL(clicked()),this,SLOT(enableSubTitleLineEdit()));
	connect(prixCheckBox,SIGNAL(clicked()),this,SLOT(enablePrixLineEdit()));
	connect(quantityCheckBox,SIGNAL(clicked()),this,SLOT(enableQuantitySpinBox()));
	connect(savePushButton,SIGNAL(clicked()),this,SLOT(getTitle()));
	
	connect(yearCheckBox,SIGNAL(clicked()),this,SLOT(enableDateEdit()));
	connect(bookIdCheckBox,SIGNAL(clicked()),this,SLOT(enableBookIdLineEditSlot()));
	
	
	//connect(savePushButton,SIGNAL(clicked()),this,SLOT(getSubTitle()));
	
	
	
	
	
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
    
    numInventaireLineEdit->setStyleSheet("QLineEdit"
    "{"
        "background-color:#FFFF99;"
        "border-bottom-left-radius: 8px;"
        "border-top-right-radius: 8px;"
        "border: 3px solid #acacac;"
        "border-top: 3px solid #acacac none;"
    "}"
    );
}

void bookCommand::init()
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

QSqlQueryModel modelDepartment;
modelDepartment.setQuery(strDepartmentQuery);

QStringList strDepartmentList;
QStringList actionList;
actionList<<"Selectionner une action"<<"Emprunt"<<"Remise";

for(int i = 2; i < modelDepartment.rowCount(); ++i)
{
	QString strDepart = modelDepartment.record(i).value("departmentname").toString();
	strDepartmentList.append(strDepart);
}
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
}

void bookCommand::selectButtonSlot()
{

if(status)
{
actionComboBox->setEnabled(false);
dateEdit->setEnabled(false);
selectPushButton->setEnabled(false);
newSelectionPushButton->setEnabled(true);
status = false;
}
else
{
actionComboBox->setEnabled(true);
dateEdit->setEnabled(true);
selectPushButton->setEnabled(true);
}

}

void bookCommand::selectNewButton()
{
if(!status)
{
actionComboBox->setEnabled(true);
dateEdit->setEnabled(true);
selectPushButton->setEnabled(true);
newSelectionPushButton->setEnabled(false);
status = true;
}
}

void bookCommand::initWidget()
{
titleGroupBox = new QGroupBox;
titleGroupBox->setTitle(tr("Titre"));

subTitleGroupBox = new QGroupBox;
subTitleGroupBox->setTitle(tr("Sous titre"));

subTitleCheckBox = new QCheckBox(tr("Sous titre"));
subTitleCheckBox->setCheckable(true);

prixCheckBox = new QCheckBox(tr("Prix"));
prixCheckBox->setCheckable(true);

personalIdGridlayout = new QGridLayout;
facultyGridlayout = new QGridLayout;
subTitleGridLayout = new QGridLayout;
marksGridlayout2 = new QGridLayout;

modeAcquisitionLabel = new QLabel(tr("<h3>Mode d'acquisition</h3>"));

labelName = new QLabel(tr("<h3>Titre du livre</h3>"));
postNameLabel = new QLabel(tr("<h3>Nom de l'auteur</h3>"));
bookIdCheckBox = new QCheckBox(tr("ISBN"));
facultyLabel = new QLabel(tr("Nom de l'empreinteur"));
departmentLabel = new QLabel(tr("Departement"));
classLabel = new QLabel(tr("Prenom de l'empreinteur"));
numInventaireLabel = new QLabel(tr("<h3>Num inventaire</h3>"));

quantityCheckBox = new QCheckBox(tr("Quantité"));
quantityCheckBox->setCheckable(true);

bookTitleLineEdit = new QLineEdit;
bookTitleLineEdit->setFixedSize(350,30);
bookAuthorLineEdit = new QLineEdit;
bookAuthorLineEdit->setFixedSize(350,30);
bookIdLineEdit = new QLineEdit;
bookIdLineEdit->setFixedSize(350,30);
bookIdLineEdit->hide();

quantitySpinBox = new QSpinBox;
quantitySpinBox->setFixedSize(377,30);
quantitySpinBox->hide();
quantitySpinBox->setMinimum(1);

subTitleLineEdit = new QLineEdit;
subTitleLineEdit->setFixedSize(377,30);
subTitleLineEdit->hide();

actionComboBox = new QComboBox;
modeAcquisitionComboBox = new QComboBox;
modeAcquisitionComboBox->addItem("Selectionner le mode");
modeAcquisitionComboBox->setFixedSize(350,30);

int index0 = modeAcquisitionComboBox->findText("Selectionner le mode");
qobject_cast<QStandardItemModel *>(modeAcquisitionComboBox->model())->item( index0 )->setEnabled( false );

QSqlQueryModel model;
QString strQuery = QString("SELECT modeacq FROM modeacquisitionindextable");
model.setQuery(strQuery);

QString strmodeAcq;
for(int i = 0; i<model.rowCount(); i++)
{
strmodeAcq = model.record(i).value("modeacq").toString();
modeAcquisitionComboBox->addItem(strmodeAcq);
}
prixLineEdit = new QLineEdit;
prixLineEdit->setFixedSize(377,30);
prixLineEdit->setEnabled(false);
prixLineEdit->hide();
dateEdit = new QDateEdit(QDate::currentDate());
dateEdit->hide();
dateEdit->setFixedSize(100,30);

numInventaireLineEdit = new QLineEdit;
numInventaireLineEdit->setFixedSize(350,30);


okPushButtonRecord = new QPushButton(tr("Save"));
okPushButtonRecord->setFixedSize(60,30);
morePushButton = new QPushButton(tr("&More>>"));
morePushButton->setFixedSize(60,30);
selectPushButton = new QPushButton(tr("Selection"));
selectPushButton->hide();
newSelectionPushButton = new QPushButton(tr("Nouvelle selection"));
newSelectionPushButton->hide();
savePushButton = new QPushButton(tr("Save"));
closePushButton = new QPushButton(tr("&Ok"));
//========== Grid
personalIdGridlayout->addWidget(labelName,0,0);
personalIdGridlayout->addWidget(bookTitleLineEdit,0,1,1,2);

personalIdGridlayout->addWidget(postNameLabel,1,0);
personalIdGridlayout->addWidget(bookAuthorLineEdit,1,1,1,2);

personalIdGridlayout->addWidget(numInventaireLabel,2,0);
personalIdGridlayout->addWidget(numInventaireLineEdit,2,1,1,2);





personalIdGridlayout->addWidget(modeAcquisitionLabel,3,0);
personalIdGridlayout->addWidget(modeAcquisitionComboBox,3,1,1,2);

//====================================================================
personalIdGridlayout->addWidget(bookIdCheckBox,4,0);
personalIdGridlayout->addWidget(bookIdLineEdit,4,1,1,2);
//====================================================================

facultyGridlayout->setEnabled(false);
//============Grid

subTitleGridLayout->addWidget(subTitleCheckBox,0,0);
subTitleGridLayout->addWidget(subTitleLineEdit,0,1,1,5);

subTitleGridLayout->addWidget(prixCheckBox,1,0);
subTitleGridLayout->addWidget(prixLineEdit,1,1,1,5);

subTitleGridLayout->addWidget(quantityCheckBox,2,0);
subTitleGridLayout->addWidget(quantitySpinBox,2,1,1,5);

yearCheckBox = new QCheckBox(tr("Année publication"));
yearCheckBox->setCheckable(true);

subTitleGridLayout->addWidget(yearCheckBox,3,0);
subTitleGridLayout->addWidget(dateEdit,3,1,1,5);

subTitleGridLayout->addWidget(selectPushButton,4,4);
subTitleGridLayout->addWidget(newSelectionPushButton,4,5);

subTitleGridLayout->setEnabled(false);
marksGridlayout2->setEnabled(false);
closeHBoxLayout = new QHBoxLayout;

closeHBoxLayout->addStretch();
okPushButtonRecord->hide();
closeHBoxLayout->addWidget(savePushButton);
closeHBoxLayout->addWidget(closePushButton);
personalIdVBox = new QVBoxLayout;
personalIdVBox->addLayout(personalIdGridlayout);
personalIdVBox->addLayout(facultyGridlayout);
titleGroupBox->setLayout(personalIdVBox);
marksVBox = new QVBoxLayout;
marksVBox->addLayout(subTitleGridLayout);
subTitleGroupBox->setLayout(marksVBox);
mainVBoxLayout = new QVBoxLayout;
mainVBoxLayout->addWidget(titleGroupBox);
mainVBoxLayout->addWidget(subTitleGroupBox);

mainVBoxLayout->addLayout(closeHBoxLayout);
setLayout(mainVBoxLayout);
}

bool bookCommand::bookIdValidation(QString bookid)
{
if(bookid.isEmpty())
{
QMessageBox::information(0,tr("Information"),tr("Vérifier les informations qui manquent."));
return false;
}
return true;
}

void bookCommand::showSaveButton()
{
if(morePushButton->isChecked())
{
savePushButton->show();
}
else
{
savePushButton->hide();
}

}

void bookCommand::enableSubTitleLineEdit()
{
if(subTitleCheckBox->isChecked())
{
subTitleLineEdit->setEnabled(true);
subTitleLineEdit->show();
}
else
{
subTitleLineEdit->setEnabled(false);
subTitleLineEdit->hide();
}
}

void bookCommand::enablePrixLineEdit()
{
if(prixCheckBox->isChecked())
{
prixLineEdit->setEnabled(true);
prixLineEdit->show();
}
else
{
prixLineEdit->setEnabled(false);
prixLineEdit->hide();
}
}

void bookCommand::enableQuantitySpinBox()
{
if(quantityCheckBox->isChecked())
{
quantitySpinBox->setEnabled(true);
quantitySpinBox->show();
}
else
{
quantitySpinBox->setEnabled(false);
quantitySpinBox->hide();
}
}


QString bookCommand::getNumInv()
{
QString numInv = numInventaireLineEdit->text();
return numInv;
}

void bookCommand::getIsbn()
{
QString numInv = numInventaireLineEdit->text();
QString isbn = bookIdLineEdit->text();
QString strNumInvQuery = QString("INSERT INTO numinvisbntable VALUES(%0%1%2,%3%4%5)").arg("'").arg(numInv).
arg("'").arg("'").arg(isbn).arg("'");
QSqlQueryModel queryModel;
queryModel.setQuery(strNumInvQuery);

}


void bookCommand::getTitle()
{
bool acquisitionmode = modeAcquisistion();

if(acquisitionmode)
{
QString title = bookTitleLineEdit->text();
QString author = bookAuthorLineEdit->text();
QString numInv = getNumInv();
bool validNumInv = bookIdValidation(numInv);
QString strQuery = QString("INSERT INTO booktitle VALUES(%0%1%2,%3%4%5,%6%7%8)").arg("'").arg(numInv).arg("'").arg("'").arg(title).
arg("'").arg("'").arg(author).arg("'");
qDebug()<<strQuery;

QSqlQueryModel queryModel;
if(validNumInv)
{
queryModel.setQuery(strQuery);
if(subTitleCheckBox->isChecked())
{
getSubTitle();
}
if(prixCheckBox->isChecked())
{
getPrice();
}

if(bookIdCheckBox->isChecked())
{
getIsbn();
}


getQuantity();

getPubYear();
clearTitle();

}

}
//acquisitionmode = false;
}

void bookCommand::getSubTitle()
{
QString numInv = getNumInv();
bool subTitleChecked = subTitleCheckBox->isChecked();
if(subTitleChecked)
{
QString strSubTitle = subTitleLineEdit->text();

if(!strSubTitle.isEmpty())
{
QString strQuery = QString("INSERT INTO subtitlebook VALUES(%0%1%2,%3%4%5)").arg("'").arg(numInv).arg("'").arg("'").arg(strSubTitle).
arg("'");
QSqlQueryModel model;
model.setQuery(strQuery);
subTitleLineEdit->clear();
}
else
{
QMessageBox::information(0,tr(""),tr("Le sous titre ne peut pas être null"));
}
}

}

void bookCommand::clearTitle()
{
bookTitleLineEdit->clear();
bookAuthorLineEdit->clear();
numInventaireLineEdit->clear();

}




void bookCommand::getPrice()
{
QString numInv = getNumInv();
bool prixChecked = prixCheckBox->isChecked();
if(prixChecked)
{
float strPrice = prixLineEdit->text().toFloat();

if(!(strPrice==0.0))
{
QString strQuery = QString("INSERT INTO bookprice VALUES(%0%1%2,%3)").arg("'").arg(numInv).arg("'").arg(strPrice);
QSqlQueryModel model;
model.setQuery(strQuery);
prixLineEdit->clear();
}
else
{
QMessageBox::information(0,tr(""),tr("Le prix ne peut pas être null"));
}
}
prixLineEdit->clear();
}

void bookCommand::getQuantity()
{
int quantity;
QString numInv = getNumInv();
bool quantityChecked = quantityCheckBox->isChecked();
if(quantityChecked)
{
quantity = quantitySpinBox->value();
}
else
{
quantity = 1;
}

QString strQuery = QString("INSERT INTO quantitytable VALUES(%0%1%2,%3)").arg("'").arg(numInv).arg("'").arg(quantity);
QSqlQueryModel model;
model.setQuery(strQuery);
quantitySpinBox->setValue(1);

}


bool bookCommand::modeAcquisistion()
{
int modeAcComboCurrentIndex = modeAcquisitionComboBox->currentIndex();
if(!(modeAcComboCurrentIndex==0))
{
QString numInv = getNumInv();
if(!numInv.isEmpty())
{
QString strQuery = QString("INSERT INTO acquisitiontable VALUES(%0%1%2,%3)").arg("'").arg(numInv).arg("'").arg(modeAcComboCurrentIndex);
QSqlQueryModel model;
model.setQuery(strQuery);
}
modeAcquisitionComboBox->setCurrentIndex(0);
return true;

}
else
{
QMessageBox::information(0,tr("Information"),tr("Selectionner le mode d'acquisition"));
return false;
}

}



void bookCommand::enableDateEdit()
{
if(yearCheckBox->isChecked())
{
dateEdit->setEnabled(true);
dateEdit->show();
selectPushButton->show();
newSelectionPushButton->show();
}
else
{
dateEdit->setEnabled(false);
dateEdit->hide();
selectPushButton->hide();
newSelectionPushButton->hide();
}
}

void bookCommand::getPubYear()
{
QString numInv = getNumInv();
QString strPubYear;
if(yearCheckBox->isChecked())
{
strPubYear = dateEdit->text();
}
else
{
strPubYear = QString("00/00/0000");
}
QStringList list = strPubYear.split("/");
strPubYear = QString("%0/%1/%2").arg(list.at(0)).arg(list.at(1)).arg(list.at(2));
QString strPubYearQuery =  QString("INSERT INTO publicationyear VALUES(%0%1%2,%3%4%5)").arg("'").arg(numInv).arg("'").
arg("'").arg(strPubYear).arg("'");
QSqlQueryModel model;
model.setQuery(strPubYearQuery);
}

void bookCommand::enableBookIdLineEditSlot()
{
if(bookIdCheckBox->isChecked())
{
bookIdLineEdit->show();
}
else
{
bookIdLineEdit->hide();
}
}

