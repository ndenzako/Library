#include<QtGui>
#include"catalogage.h"
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
#include<QSpinBox>
#include<QDebug>
#include<QSqlRecord>
#include<QCheckBox>
catalogageDialog::catalogageDialog(QWidget *parent)
: QDialog(parent)
{
	
	setWindowTitle(tr("Catalogage"));
	initWidget();
	init();
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	
	status = false;
	connect(closePushButton,SIGNAL(clicked()),this,SLOT(accept()));
	connect(savePushButton,SIGNAL(clicked()),this,SLOT(bookIdValidation()));
	connect(numInventaireLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(activateSaveButton()));
	connect(exemplaireCheckBox,SIGNAL(clicked()),this,SLOT(enableExemplaireSlot()));
	connect(savePushButton,SIGNAL(clicked()),this,SLOT(isbCkeckSlot()));
	connect(commentCheckBox,SIGNAL(clicked()),this,SLOT(enableCommentLineEditSlot()));
	
	
	
	
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


void catalogageDialog::init()
{
isbCkeck = false;
QString strTypeQuery = QString("SELECT typename FROM booktypetable");
QSqlQueryModel bookTypeQuery;
bookTypeQuery.setQuery(strTypeQuery);
QString strBookType;
for(int i = 0; i<bookTypeQuery.rowCount();i++)
{
strBookType = bookTypeQuery.record(i).value("typename").toString();
bookTypeCombo->addItem(strBookType);
}
}

//==================================================================================
void catalogageDialog::initWidget()
{
personalIdGroupBox = new QGroupBox;
personalIdGroupBox->setTitle(tr("Catalogage"));
facultyGroupBox = new QGroupBox;

personalIdGridlayout = new QGridLayout;
facultyGridlayout = new QGridLayout;
//marksGridlayout1 = new QGridLayout;
marksGridlayout2 = new QGridLayout;

labelName = new QLabel(tr("<h3>Num inventaire</h3>"));
postNameLabel = new QLabel(tr("<h3>Côte</h3>"));
studentIdLabel = new QLabel(tr("<h3>Type du livre</h3>"));
localisationLabel = new QLabel(tr("<h3>Localisation</h3>"));
exemplaireCheckBox = new QCheckBox(tr("Numero d'exemplaire"));
exemplaireCheckBox->setCheckable(true);

commentCheckBox = new QCheckBox(tr("Commentaire"));
commentCheckBox->setCheckable(true);

departmentMLabel = new QLabel(tr("Service"));

bookTypeCombo = new QComboBox;

bookTypeCombo->setFixedSize(350,30);
bookCoteLineEdit = new QLineEdit;
bookCoteLineEdit->setFixedSize(350,30);
numInventaireLineEdit = new QLineEdit;
numInventaireLineEdit->setFixedSize(350,30);
commentLineEdit = new QLineEdit;
commentLineEdit->setEnabled(false);
commentLineEdit->hide();
commentLineEdit->setFixedSize(300,30);

bookLocalisationCombo = new QComboBox;
bookLocalisationCombo->setFixedSize(300,30);

    QString strDepartQuery = QString("SELECT DISTINCT departmentName FROM department");
    QSqlQueryModel departQuery;
    departQuery.setQuery(strDepartQuery);
    QStringList list;
    for(int i = 0 ;i<departQuery.rowCount(); i++)
    {
    list.append(departQuery.record(i).value("departmentName").toString());
    }
    bookLocalisationCombo->addItems(list);
    int index0;
    for(int i = 0; i<list.size();i++)
    {
    index0 = bookLocalisationCombo->findText(list.at(i));
    if(!(list.at(i)=="Section Polytechnique"))
    {
    qobject_cast<QStandardItemModel *>(bookLocalisationCombo->model())->item( index0 )->setEnabled( false );
    }
    }
    bookLocalisationCombo->setCurrentIndex(3);
numberExemplaireSpinBox = new QSpinBox;
numberExemplaireSpinBox->setFixedSize(300,30);
numberExemplaireSpinBox->setMinimum(1);
numberExemplaireSpinBox->hide();

actionComboBox = new QComboBox;

dateEdit = new QDateEdit(QDate::currentDate());
okPushButtonRecord = new QPushButton(tr("Save"));
okPushButtonRecord->setFixedSize(60,30);

selectPushButton = new QPushButton(tr("Selection"));

savePushButton = new QPushButton(tr("Save"));
savePushButton->setEnabled(false);
closePushButton = new QPushButton(tr("&Ok"));

//========== Grid
personalIdGridlayout->addWidget(labelName,0,0);
personalIdGridlayout->addWidget(numInventaireLineEdit,0,1,1,2);

personalIdGridlayout->addWidget(postNameLabel,1,0);
personalIdGridlayout->addWidget(bookCoteLineEdit,1,1,1,2);

personalIdGridlayout->addWidget(studentIdLabel,2,0);
personalIdGridlayout->addWidget(bookTypeCombo,2,1,1,2);
//==========



facultyGridlayout->addWidget(localisationLabel,0,0);
facultyGridlayout->addWidget(bookLocalisationCombo,0,1,1,2);

facultyGridlayout->addWidget(exemplaireCheckBox,1,0);
facultyGridlayout->addWidget(numberExemplaireSpinBox,1,1,1,2);
facultyGridlayout->addWidget(commentCheckBox,2,0);
facultyGridlayout->addWidget(commentLineEdit,2,1,1,2);

marksGridlayout2->addWidget(savePushButton,2,3);

closeHBoxLayout = new QHBoxLayout;
closeHBoxLayout->addStretch();

closeHBoxLayout->addWidget(savePushButton);
closeHBoxLayout->addWidget(closePushButton);

personalIdVBox = new QVBoxLayout;
personalIdVBox->addLayout(personalIdGridlayout);
personalIdVBox->addLayout(facultyGridlayout);

personalIdGroupBox->setLayout(personalIdVBox);

mainVBoxLayout = new QVBoxLayout;

mainVBoxLayout->addWidget(personalIdGroupBox);
mainVBoxLayout->addLayout(closeHBoxLayout);
setLayout(mainVBoxLayout);
}

void catalogageDialog::bookIdValidation()
{
QString bookid = numInventaireLineEdit->text();
if(bookid.isEmpty())
{
QMessageBox::critical(0,tr("Information"),tr("Commande invalide."));
}
}


/*void catalogageDialog::getCatalogueTable()
{

}*/

void catalogageDialog::isbCkeckSlot()
{
QString strTempNuminv = numInventaireLineEdit->text();
QString strNuminvSearch = QString("SELECT numinv FROM booktitle WHERE numinv LIKE '%0%'").arg(strTempNuminv);
QSqlQueryModel numinvQuery;
numinvQuery.setQuery(strNuminvSearch);
QStringList numinvList;
QString strNuminv;
for(int i = 0; i <numinvQuery.rowCount();i++)
{
strNuminv = numinvQuery.record(i).value("numinv").toString();
numinvList.append(strNuminv);
}

//Check if the isbn typep in is right

if((numinvList.size()==1)&&(numinvList.at(0)==strTempNuminv))
{
QString strBookId = numInventaireLineEdit->text();

qDebug()<<strNuminvSearch;
strTempNuminv = numinvList.at(0);
QMessageBox::information(0,tr("Information"),tr("Numéro d'inventaire trouvé dans la base de donnée"));
isbCkeck = true;


/*else
{
QMessageBox::information(0,tr("Information"),tr("ISBN pas disponible dans la base de donnee"));
isbCkeck = false;
qDebug()<<strIsbnSearch;
}*/

int exemplaireNUm;
QString exemplaireStr;
if(exemplaireCheckBox->isChecked())
{
QString srtExemplaire = numInventaireLineEdit->text();
exemplaireNUm = numberExemplaireSpinBox->value();
QString strNumberExempalire = QString("SELECT quantity FROM quantitytable WHERE numinv =%0%1%2").arg("'").arg(srtExemplaire).arg("'");
qDebug()<<strNumberExempalire;
QSqlQueryModel exemplaireQuery;
exemplaireQuery.setQuery(strNumberExempalire);
int numExempltemp = exemplaireQuery.record(0).value("quantity").toInt();
qDebug()<<"From the database"<<numExempltemp;
qDebug()<<"From the spin box"<<exemplaireNUm;
if(exemplaireNUm <= numExempltemp)
{
exemplaireStr = QString("EX%0").arg(QString::number(exemplaireNUm));
}
else
{
QMessageBox::information(this,tr("Information"),tr("Le nombre fourni est en dehors du nombre d'exemplaires disponibles. Merci"));
}
}
else
{
exemplaireStr = "";
}

QString strBookCote = bookCoteLineEdit->text();
int booktype = bookTypeCombo->currentIndex();

//In the future, localisation will be general to cover all occurences
int booklocalisation = bookLocalisationCombo->currentIndex();

QString strCatalogueQuery = QString("INSERT INTO cataloguetable VALUES(%0%1%2,%3%4%5,%6,%7)").arg("'").
arg(strTempNuminv).arg("'").arg("'").arg(strBookCote).arg("'").arg(booktype).arg(booklocalisation);

qDebug()<<strCatalogueQuery;
QString strExemplaire = QString("INSERT INTO exemplairetable VALUES(%0%1%2,%3%4%5)").arg("'").arg(strTempNuminv).arg("'").
arg("'").arg(exemplaireStr).arg("'");

qDebug()<<strExemplaire;
QSqlQueryModel exemplaireQuery;
exemplaireQuery.setQuery(strCatalogueQuery);
exemplaireQuery.setQuery(strExemplaire);
getComment();
}

}

void catalogageDialog::enableExemplaireSlot()
{
if(exemplaireCheckBox->isChecked())
{
numberExemplaireSpinBox->show();
}
else
{
numberExemplaireSpinBox->hide();
}
}

void catalogageDialog::activateSaveButton()
{
QString strTempNuminv = numInventaireLineEdit->text();
QString strNuminvSearch = QString("SELECT numinv FROM booktitle WHERE numinv LIKE '%0%'").arg(strTempNuminv);
QSqlQueryModel numinvQuery;
numinvQuery.setQuery(strNuminvSearch);
QStringList numinvList;
QString strNuminv;
for(int i = 0; i <numinvQuery.rowCount();i++)
{
strNuminv = numinvQuery.record(i).value("numinv").toString();
numinvList.append(strNuminv);
}

//Check if the isbn typep in is right

if((numinvList.size()==1)&&(numinvList.at(0)==strTempNuminv))
{
savePushButton->setEnabled(true);
}
else
{
savePushButton->setEnabled(false);
}
}

void catalogageDialog::enableCommentLineEditSlot()
{
if(commentCheckBox->isChecked())
{
commentLineEdit->show();
commentLineEdit->setEnabled(true);
}
else
{
commentLineEdit->hide();
commentLineEdit->setEnabled(false);
}
}

void catalogageDialog::getComment()
{
if(commentCheckBox->isChecked())
{
QString strCommment = commentLineEdit->text();
if(!strCommment.isEmpty())
{
QString strNumInv = numInventaireLineEdit->text();
QString strCommentQuery = QString("INSERT INTO commenttable VALUES(%0%1%2,%3%4%5)").arg("'").arg(strNumInv).arg("'").arg("'").
arg(strCommment).arg("'");
QSqlQueryModel queryModel;
queryModel.setQuery(strCommentQuery);
qDebug()<<strCommentQuery;
}
else
{
QMessageBox::information(this,tr("Information"),tr("Commentaire vide pas admis"));
}
}

}


