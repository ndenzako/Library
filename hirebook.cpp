#include<QtGui>
#include"hirebook.h"
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
#include<QSqlRecord>
#include<QSpinBox>
#include<QCheckBox>
hireBook::hireBook(QWidget *parent)
: QDialog(parent)
{
	setWindowTitle(tr("Emprunter un livre"));
	initWidget();
	init();
	
	QString strDate = getDate();
	qDebug()<<"The current date is "<<strDate<<"The last index"<<findLastIndex();
	hireBookGroupBox->hide();
	bringbackBookGroupBox->hide();
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	morePushButton->setCheckable(true);
	status = true;
	connect(morePushButton, SIGNAL(toggled(bool)), this, SLOT(showSaveButton()));
	connect(morePushButton, SIGNAL(toggled(bool)), hireBookGroupBox, SLOT(setVisible(bool)));
	//activateGroupBox();
	connect(morePushButton, SIGNAL(toggled(bool)), bringbackBookGroupBox, SLOT(setVisible(bool)));
	connect(selectPushButton, SIGNAL(clicked()), this, SLOT(selectButtonSlot()));
	connect(newSelectionPushButton, SIGNAL(clicked()), this, SLOT(selectNewButton()));
	connect(closePushButton,SIGNAL(clicked()),this,SLOT(accept()));
	connect(savePushButton,SIGNAL(clicked()),this,SLOT(bookIdValidation()));
	//connect(actionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(activateMoreButton()));
	connect(actionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(activateGroupBox()));
	connect(hireBookCheckBox,SIGNAL(clicked()),this,SLOT(enableNumExemplaireSlot()));
	connect(bookIdLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(searchBook()));
	//connect(numInventaireLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(activateSaveButton()));
	connect(savePushButton,SIGNAL(clicked()),this,SLOT(saveHireBookData()));

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

int hireBook::lastIndex = 0;

void hireBook::init()
{
lastIndex = findLastIndex();
QString strActionQuery = QString("SELECT DISTINCT actionName FROM actiontable");
QSqlQueryModel actionQuery;
actionQuery.setQuery(strActionQuery);
QStringList actionList;
for(int i = 0; i<actionQuery.rowCount();i++)
{
actionList.append(actionQuery.record(i).value("actionName").toString());

}

actionComboBox->addItems(actionList);

int index0 = actionComboBox->findText("Selectionner une action");
qobject_cast<QStandardItemModel *>(actionComboBox->model())->item( index0 )->setEnabled( false );
    
    QString strDepartQuery = QString("SELECT DISTINCT departmentName FROM department");
    QSqlQueryModel departQuery;
    departQuery.setQuery(strDepartQuery);
    QStringList list;
    for(int i = 0 ;i<departQuery.rowCount(); i++)
    {
    list.append(departQuery.record(i).value("departmentName").toString());
    }
    departmentComboBox->addItems(list);
}

void hireBook::selectButtonSlot()
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

void hireBook::selectNewButton()
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
//==================================================================================
void hireBook::initWidget()
{
hireBookGroupBox = new QGroupBox;
hireBookGroupBox->setTitle(tr("Libérer la commande"));

bringbackBookGroupBox = new QGroupBox;
bringbackBookGroupBox->setTitle(tr("Remise"));
bringbackBookGroupBox->setEnabled(false);
facultyGroupBox = new QGroupBox;
marksGroupBox = new QGroupBox;
marksGroupBox->setTitle(tr("Service de prêt"));

personalIdGridlayout = new QGridLayout;
facultyGridlayout = new QGridLayout;
marksGridlayout1 = new QGridLayout;
marksGridlayout2 = new QGridLayout;
bringbackBookGridlayout = new QGridLayout;

labelName = new QLabel(tr("<h3>Titre du livre</h3>"));

studentIdLabel = new QLabel(tr("<h3>Numéro inventaire</h3>"));
facultyLabel = new QLabel(tr("<h3>Nom emprunteur</h3>"));
departmentLabel = new QLabel(tr("<h3>Departement</h3>"));
classLabel = new QLabel(tr("<h3>Prenom emprunteur</h3>"));

//hireBookLabel = new QLabel(tr("<h3>Numero d'exemplaire</h3>"));
numExemplaireSpinBox = new QSpinBox;
numExemplaireSpinBox->hide();
numExemplaireSpinBox->setMinimum(1);

departmentMLabel = new QLabel(tr("<h3>Service</h3>"));

numInventaireLabel = new QLabel(tr("<h3>Numéro inventaire</h3>"));
nomEmprunteurLabel = new QLabel(tr("<h3>Nom emprunteur</h3>"));

bookTitleCombo = new QComboBox;

bookTitleCombo->setFixedSize(350,30);

bookIdLineEdit = new QLineEdit;
bookIdLineEdit->setFixedSize(350,30);
nomEmprunteurLineEdit = new QLineEdit;
nomEmprunteurLineEdit->setFixedSize(300,30);
departmentComboBox = new QComboBox;

prenomEmprunteur = new QLineEdit;
prenomEmprunteur->setFixedSize(300,30);

numInventaireLineEdit = new QLineEdit;
numInventaireLineEdit->setFixedSize(300,30);

actionComboBox = new QComboBox;
nomEmprunteurComboBox = new QComboBox;
nomEmprunteurComboBox->setFixedSize(300,30);
dateEdit = new QDateEdit(QDate::currentDate());
okPushButtonRecord = new QPushButton(tr("Save"));
okPushButtonRecord->setFixedSize(60,30);
morePushButton = new QPushButton(tr("&More>>"));

morePushButton->setFixedSize(60,30);
selectPushButton = new QPushButton(tr("Selection"));
newSelectionPushButton = new QPushButton(tr("Nouvelle selection"));
newSelectionPushButton->setEnabled(false);
savePushButton = new QPushButton(tr("Save"));
savePushButton->hide();
closePushButton = new QPushButton(tr("&Ok"));

hireBookCheckBox = new QCheckBox;
hireBookCheckBox->setText("Numéro d'exemplaire");
//========== Grid
personalIdGridlayout->addWidget(labelName,0,0);
personalIdGridlayout->addWidget(bookTitleCombo,0,1,1,2);

personalIdGridlayout->addWidget(studentIdLabel,1,0);
personalIdGridlayout->addWidget(bookIdLineEdit,1,1,1,2);
//==========

//==========Grid
facultyGridlayout->addWidget(facultyLabel,0,0);
facultyGridlayout->addWidget(nomEmprunteurLineEdit,0,1,1,2);

facultyGridlayout->addWidget(classLabel,1,0);
facultyGridlayout->addWidget(prenomEmprunteur,1,1,1,2);

facultyGridlayout->addWidget(hireBookCheckBox,2,0);
facultyGridlayout->addWidget(numExemplaireSpinBox,2,1,1,2);

facultyGridlayout->addWidget(departmentLabel,3,0);
facultyGridlayout->addWidget(departmentComboBox,3,1,1,2);

//============Grid
marksGridlayout1->addWidget(departmentMLabel,0,0);
marksGridlayout1->addWidget(actionComboBox,0,1,1,5);

yearLabel = new QLabel;
yearLabel->setText(tr("<h3>Date de l'opération</h3>"));
marksGridlayout1->addWidget(yearLabel,2,0);
marksGridlayout1->addWidget(dateEdit,2,1,1,5);

marksGridlayout1->addWidget(selectPushButton,3,4);
marksGridlayout1->addWidget(newSelectionPushButton,3,5);
//=============
bringbackBookGridlayout->addWidget(numInventaireLabel,0,0);
bringbackBookGridlayout->addWidget(numInventaireLineEdit,0,1,1,2);
bringbackBookGridlayout->addWidget(nomEmprunteurLabel,1,0);
bringbackBookGridlayout->addWidget(nomEmprunteurComboBox,1,1,1,2);
bringbackBookGroupBox->setLayout(bringbackBookGridlayout);

marksGridlayout2->addWidget(savePushButton,2,3);

closeHBoxLayout = new QHBoxLayout;
closeHBoxLayout->addStretch();
closeHBoxLayout->addWidget(morePushButton);
okPushButtonRecord->hide();
closeHBoxLayout->addWidget(savePushButton);
closeHBoxLayout->addWidget(closePushButton);

personalIdVBox = new QVBoxLayout;
personalIdVBox->addLayout(personalIdGridlayout);
personalIdVBox->addLayout(facultyGridlayout);

hireBookGroupBox->setLayout(personalIdVBox);
hireBookGroupBox->setEnabled(false);
marksVBox = new QVBoxLayout;
marksVBox->addLayout(marksGridlayout1);
marksVBox->addLayout(marksGridlayout2);
marksGroupBox->setLayout(marksVBox);

mainVBoxLayout = new QVBoxLayout;

mainVBoxLayout->addWidget(marksGroupBox);
mainVBoxLayout->addWidget(hireBookGroupBox);
mainVBoxLayout->addWidget(bringbackBookGroupBox);
mainVBoxLayout->addLayout(closeHBoxLayout);
setLayout(mainVBoxLayout);
}

void hireBook::bookIdValidation()
{
QString bookid = bookIdLineEdit->text();
if(bookid.isEmpty())
{
QMessageBox::critical(0,tr("Information"),tr("Commande invalide."));
}
}

void hireBook::showSaveButton()
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

void hireBook::activateGroupBox()
{
int currIndex = actionComboBox->currentIndex();
switch(currIndex)
{
case 1:
{
hireBookGroupBox->setEnabled(true);
bringbackBookGroupBox->setEnabled(false);
break;
}
case 2:
{
hireBookGroupBox->setEnabled(false);
bringbackBookGroupBox->setEnabled(true);
break;
}
}
}

void hireBook::enableNumExemplaireSlot()
{
if(hireBookCheckBox->isChecked())
{
numExemplaireSpinBox->show();
}
else
{
numExemplaireSpinBox->hide();
}
}

int hireBook::getBookQuantity(const QString numinv)
{
QString strQantityQuery = QString("SELECT quantity FROM quantitytable WHERE numinv=%0%1%2").arg("'").arg(numinv).arg("'");
QSqlQueryModel queryModel;
queryModel.setQuery(strQantityQuery);
int quantity = queryModel.record(0).value("quantity").toInt();
return quantity;
}

bool hireBook::getService()
{
int currIndex = actionComboBox->currentIndex();
if(currIndex>0)
{
switch(currIndex)
{
case 1:
{
return true;
break;
}
case 2:
{
return false;
break;
}
}
}
}

int hireBook::getNumeroExemplaire()
{
int numExempl = numExemplaireSpinBox->value();
return numExempl;
}

void hireBook::searchBook()
{
QString srtNumInv = bookIdLineEdit->text();
QString srtBookQuery;
QSqlQueryModel queryModel;

QStringList list;
QString strTitle;
if(srtNumInv!="")
{
srtBookQuery = QString("SELECT DISTINCT title FROM booktitle WHERE numinv LIKE '%0%'")
.arg(srtNumInv);
queryModel.setQuery(srtBookQuery);
for(int i=0;i<queryModel.rowCount();i++)
{
strTitle = queryModel.record(i).value("title").toString();
list.append(strTitle);
}
}
if(list.size()>0)
{
bookTitleCombo->clear();
bookTitleCombo->addItems(list);
}
else
{
bookTitleCombo->clear();
}
//qDebug()<<srtBookQuery;
}

QString hireBook::getDate()
{
QString strDate = dateEdit->text();
return strDate;
}
QString hireBook::getNomEmprunteur()
{

QString strNom = nomEmprunteurLineEdit->text();
return strNom;
}

QString hireBook::getPrenomEmprunteur()
{
QString strPrenom = prenomEmprunteur->text();
return strPrenom;
}

int hireBook::findLastIndex()
{
QString strLastIndexQuery = QString("SELECT emprunteurId FROM hirebooktable");
QSqlQueryModel queryModel;
queryModel.setQuery(strLastIndexQuery);
int lastIndex = queryModel.record(queryModel.rowCount()-1).value("emprunteurId").toInt();
return lastIndex;
}

QString hireBook::getNuminv(const QLineEdit *bookIdLineEdit)
{
QString strBookId = bookIdLineEdit->text();
return strBookId;
}

void hireBook::saveHireBookData()
{
bool hireBookService = getService();
if(hireBookService)
{
QString strDateSortie = getDate();
QString strNuminv = getNuminv(bookIdLineEdit);
QString nomEmprunteur = getNomEmprunteur();
QString prenomEmpprunteur = getPrenomEmprunteur();
int intDepartment = getDepartment();
QString strSaveDataQuery = QString("INSERT INTO hirebooktable(nomemprunteur,prenomemprunteur,numinv,departmenId,datesortie) VALUES("
"%0%1%2,%3%4%5,%6%7%8,%9, %10%11%12)").arg("'").arg(nomEmprunteur).arg("'").arg("'").arg(prenomEmpprunteur).arg("'").arg("'")
.arg(strNuminv).arg("'").arg(intDepartment).arg("'").arg(strDateSortie).arg("'");
QSqlQueryModel queryModel;
queryModel.setQuery(strSaveDataQuery);
qDebug()<<strSaveDataQuery;

if(hireBookCheckBox->isChecked())
{
QString numinv = getNuminv(bookIdLineEdit);
int numExempl = numExemplaireSpinBox->value();
QString strNumExempl = QString("EX%0").arg(numExempl);
QString strExemplaireQuery = QString("SELECT * FROM exemplairetable WHERE numinv = %0%1%2 AND exemplaireId = %3%4%5").
arg("'").arg(numinv).arg("'").arg("'").arg(strNumExempl).arg("'");
queryModel.setQuery(strExemplaireQuery);
qDebug()<<strExemplaireQuery;
numinv = queryModel.record(0).value("numinv").toString();
strNumExempl = queryModel.record(0).value("exemplaireId").toString();
//int lastIndex = findLastIndex();
if(!(strNumExempl.isEmpty()) && !(numinv.isEmpty()))
{
QString strExemplaireQuery = QString("INSERT INTO emprunteurexemplairetable VALUES(%0,%1%2%3,%4%5%6)").arg(lastIndex+1).arg("'").
arg(numinv).arg("'").arg("'").arg(strNumExempl).arg("'");
queryModel.setQuery(strExemplaireQuery);
qDebug()<<strExemplaireQuery;
}
lastIndex+=1;
}
}
else
{
QMessageBox::warning(this,tr("Alert"),tr("Operation de remise"));
}
}

int hireBook::getDepartment()
{
int intDepartment = departmentComboBox->currentIndex();
return intDepartment;
}

/*QString hireBook::getBookTitle(QComboBox &bookTitleCombo)
{
QString strBookTitle = bookTitleCombo->currentText();
return strBookTitle;
}*/

void hireBook::resetFields()
{
bool service = getService();
if(service)
{
bookTitleCombo->clear();
bookIdLineEdit->clear();
nomEmprunteurLineEdit-clear();
prenomEmpprunteur->clear();
if(hireBookCheckBox->isChecked())
{
numExemplaireSpinBox->setMinimum(1);
}
departmentComboBox->setCurrentIndex(0);
}
else
{
numInventaireLineEdit->clear();
nomEmprunteurComboBox->clear();
}
}
