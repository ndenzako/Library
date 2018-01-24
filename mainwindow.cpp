//#include"spreadsheet.h"
#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"bookcommand.h"
#include"searchbook.h"

#include <QtDebug>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QVBoxLayout>
#include<QComboBox>
#include<QGridLayout>
#include<QGroupBox>
#include<QAction>
#include<QTextEdit>
#include<QDialog>
#include<QTextBrowser>
#include"hirebook.h"
#include"history.h"
#include"catalogage.h"
#include"aboutus.h"
#include"admin.h"

int MainWindow::counter=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralWidget_2);
ui->label->setPixmap(QPixmap(":/images/icon.png"));
setWindowIcon(QPixmap(":/images/icon.png"));
setWindowTitle(tr("QEULibrary software"));
createMenu();


    showMaximized();
QStringList list;
list<<"Admin"<<"Guest";
ui->acoubtComboBox->addItems(list);
connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(establishConnection()));
connect(ui->pwdLineEdit,SIGNAL(returnPressed()),this,SLOT(establishConnection()));
connect(ui->usrLineEdit,SIGNAL(returnPressed()),this,SLOT(establishConnection()));
//connect(newRecordAction,SIGNAL(triggered()),this, SLOT(newEntryData()));
//connect(recordAction,SIGNAL(triggered()),this, SLOT(spreadsheetViewer()));
connect(exitAction,SIGNAL(triggered()),qApp, SLOT(quit()));
connect(actionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(hireBookSlot()));
connect(aboutUsAction,SIGNAL(triggered()),this, SLOT(helpAboutUs()));
connect(aboutCompanyQction,SIGNAL(triggered()),this, SLOT(helpAboutCompany()));
connect(commandeAction,SIGNAL(triggered()),this, SLOT(commandeSlot()));
connect(catalogageAction,SIGNAL(triggered()),this, SLOT(catalogageSlot()));
connect(pretAction,SIGNAL(triggered()),this, SLOT(pretSlot()));
connect(historyAction,SIGNAL(triggered()),this, SLOT(historySlot()));
connect(adminAction,SIGNAL(triggered()),this,SLOT(raiseAdminSlot()));
connect(searchAction,SIGNAL(triggered()),this,SLOT(searchBookSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    actionComboBox = new QComboBox;
    
    
    menuBar = new QMenuBar;
    menuFile = menuBar->addMenu(tr("&Fichier"));
    menuFile->setEnabled(false);
    adminMenu = menuBar->addMenu(tr("&Administration"));
    adminMenu->setEnabled(false);
    menuService = menuBar->addMenu(tr("&Services"));
    menuService->setEnabled(false);
    searchMenu = menuBar->addMenu(tr("&Rechercher"));
    searchMenu->setEnabled(false);
    menuBar->addSeparator();
    menuHelp=menuBar->addMenu(tr("&Aide"));
    menuHelp->setEnabled(false);
    aboutUsAction = new QAction(menuHelp);
    //aboutUsAction->setEnabled(false);
    aboutUsAction->setText(tr("About us"));
    menuHelp->addAction(aboutUsAction);
    
    aboutCompanyQction = new QAction(menuHelp);
    aboutCompanyQction->setText(tr("About the company"));
    menuHelp->addAction(aboutCompanyQction);
    
    
    newAction = new QAction(menuFile);
    //recordAction = new QAction(menuFile);
    //newRecordAction = new QAction(recordAction);
    exitAction = new QAction(menuFile);
    
    adminAction = new QAction(adminMenu);
    adminAction->setText(tr("Ajouter un departement"));
    adminMenu->addAction(adminAction);
    searchAction = new QAction(searchMenu);
    searchAction->setText(tr("Chercher un livre"));
    searchMenu->addAction(searchAction);
    
    
    commandeAction = new QAction(menuService);
    commandeAction->setText(tr("Service de commande et acquisiton"));
    menuService->addAction(commandeAction);
    
    catalogageAction = new QAction(menuService);
    catalogageAction->setText(tr("Service de catalogage"));
    menuService->addAction(catalogageAction);
    
    pretAction = new QAction(menuService);
    pretAction->setText(tr("Service de prêt"));
    menuService->addAction(pretAction);
    
    historyAction = new QAction(menuService);
    historyAction->setText(tr("Historique"));
    menuService->addAction(historyAction);
    
    newAction->setText(tr("Ouvrir"));
    exitAction->setText(tr("&Quiter"));
    newAction->setEnabled(false);
    menuFile->addAction(newAction);
    menuFile->addSeparator();
    menuFile->addAction(exitAction);
    
    setMenuBar(menuBar);


}

void MainWindow::showMaximized()
{
    // ...
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
                   | Qt::WindowMaximized);
    show();
}

void MainWindow::establishConnection()
{

    
    
QString pwd;
QString usr;
counter+=1;
qDebug()<<"The remainning days: "<<counter;

pwd = ui->pwdLineEdit->text();
usr = ui->usrLineEdit->text();
int admin = ui->acoubtComboBox->currentIndex();
switch(admin)
{
case 0:
if (usr == "abc" && pwd == "abc")
{
activateMenus();
//qDebug() << "Connexction successfull";
QStringList actionlist;
actionlist<<"Sélectionner un service"<<"Service de commande et acquisition"<<"Service de catalogage"<<"Service de prêt"
<<"Voir l'historique";

ui->centralWidget_2->hide();
mainWin = new QMainWindow;
//setCentralWidget(mainWin);
QPixmap bkgnd(":/images/bgd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    
    widget = new QWidget;

logolabel = new QLabel;
logolabel->setPixmap(QPixmap(":/images/icon.png"));
welcomelabel = new QLabel(tr("<h1><font color = red>BIENVENUE A LA BIBLIOTHEQUE DE LA SECTION POLYTECHINIQUE</font></h1>"));
this->setStyleSheet("QLabel"
    "{"
        "background-color:grey;"
        "border-bottom-left-radius: 15px;"
        "border-top-right-radius: 15px;"
        "border: 5px solid #acacac;"
        "border-top: 3px solid #acacac none;"
        "margin-top: 15px;"
        "margin-left: 0px;"
        "font-size: 20px;"
        "border: 5px solid #FF00FF;"
    "}"
    "QGroupBox"
    "{"
        "background-color:transparent;"
        "border-bottom-left-radius: 8px;"
        "border-top-right-radius: 8px;"
        "border: 10px solid #660000;"
        "border-top: 10px solid #acacac;"
        "margin-top: 15px;"
        "margin-left: 0px;"
    "}"
    "QGroupBox::title"
    "{"
        "subcontrol-origin: margin;"
        "background:url(:/assets/subWindowBackground);"
        "border-top-left-radius: 3px;"
        "border-bottom-right-radius: 3px;"
        "border: 3px solid #0b477b;"
        "border-bottom: none;"
        "background-color: qlineargradient(x1: 30, y1: 10, x2: 30, y2: 10,"
            "stop: 0 #005192, stop: 1 #002f60);"
        "padding: 2 2px;"
        "color: white;"
    "}");
welcomeHBoxLayout = new QHBoxLayout;
actionHBoxLayout = new QHBoxLayout;
welcomeHBoxLayout->addStretch();
welcomeHBoxLayout->addWidget(welcomelabel);
welcomeHBoxLayout->addStretch();
logoHBoxLayout= new QHBoxLayout;
mainVBoxLayout = new QVBoxLayout(widget);

actionComboBox->addItems(actionlist);
int index0 = actionComboBox->findText("Sélectionner un service");
qobject_cast<QStandardItemModel *>(actionComboBox->model())->item( index0 )->setEnabled( false );
qDebug()<<index0;
actionHBoxLayout->addStretch();
mainGrouBox = new QGroupBox;
mainGrouBox->setTitle(tr("Choisir un service"));
mainGridLayout = new QGridLayout;
mainGridLayout->addWidget(actionComboBox);
mainGrouBox->setLayout(mainGridLayout);
actionHBoxLayout->addWidget(mainGrouBox);
actionHBoxLayout->addStretch();
logoHBoxLayout->addStretch();
logoHBoxLayout->addWidget(logolabel);
mainVBoxLayout->addLayout(welcomeHBoxLayout);
mainVBoxLayout->addLayout(logoHBoxLayout);
mainVBoxLayout->addLayout(actionHBoxLayout);
mainVBoxLayout->addStretch();
//mainWin->setLayout(mainVBoxLayout);
//widget->setPalette(palette);
setCentralWidget(widget);
setWindowTitle(tr("QEULibrary software"));
QMessageBox::information(0,tr("Connexion status"),tr("<font color =  red>You are connected on the data base.</font>"));

}
else
{
QMessageBox::information(0,tr("Connection failure"),tr("<b><i><font color = red>Wrong user name or password</font></><i/><b/>"), QMessageBox::Ok);// | QMessageBox::Retry | QMessageBox::Ignore);
}
break;
case 1:
{
QMessageBox::information(0,tr("Connection failure"),tr("Guest account not yet ready, comming soon"), QMessageBox::Ignore);
break;
}
}
}




void MainWindow::newEntryData()
{
//createConnexion();
//spreadsheet = new Spreadsheet;
addDataView = new ArtistForm("");
//setCentralWidget(spreadsheet);
//setCentralWidget(addDataView);
addDataView->exec();
//spreadsheet->show();
}

void MainWindow::hireBookSlot()
{
currentIndex = actionComboBox->currentIndex();
switch(currentIndex)
{
case 0:
{
break;
}
case 1:
{
bookCommandDialog = new bookCommand;
bookCommandDialog->exec();
break;
}
case 2:
{
catalogueDialog = new catalogageDialog;
catalogueDialog->exec();
break;
}
case 3:
{
hireBookForm = new hireBook;
hireBookForm->exec();
break;
}
case 4:
{
historyWidget = new historyDialog;
historyWidget->exec();
break;
}
default:
QMessageBox::information(0,tr("Action information"),tr("You didn't select right <br/>action, but coming soon!..."));
}

}

void MainWindow::helpAboutUs()
{
aboutUsDialog = new aboutUs;
aboutUsDialog->helpAboutUs();
aboutUsDialog->exec();
}


void MainWindow::helpAboutCompany()
{
     QMessageBox::about(this, tr("About company"),
                         tr("<h3><font color = red>Comming soon in the next generation</h3>"));
}

void MainWindow::commandeSlot()
{
bookCommandDialog = new bookCommand;
bookCommandDialog->exec();
}

void MainWindow::catalogageSlot()
{
catalogueDialog = new catalogageDialog;
catalogueDialog->exec();
}

void MainWindow::pretSlot()
{
hireBookForm = new hireBook;
hireBookForm->exec();
}
void MainWindow::historySlot()
{
 historyWidget = new historyDialog;
historyWidget->exec();
}

void MainWindow::raiseAdminSlot()
{
dialog = new adminDialog;
dialog->exec();

}

void MainWindow::activateMenus()
{

menuFile->setEnabled(true);
adminMenu->setEnabled(true);
searchMenu->setEnabled(true);
menuHelp->setEnabled(true);
menuService->setEnabled(true);
}

void MainWindow::searchBookSlot()
{
searchBookDialog = new searchDialog;
searchBookDialog->exec();
}

