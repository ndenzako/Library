#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"modelview.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QStringList;
class QMessageBox;
class QMenu;
class QAction;
//class Spreadsheet;
class QHBoxLayout;
class QVBoxLayout;
class QComboBox;
class QWidget;
class QGridLayout;
class QGroupBox;
class hireBook;
class historyDialog;
class bookCommand;
class QAction;
class QTextEdit;
class QDialog;
class catalogageDialog;
class QTextBrowser;
class aboutUs;
class adminDialog;
class searchDialog;
QT_END_NAMESPACE
//class QLabel;
//class ArtistForm;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showMaximized();
    void createMenu();
    void activateMenus();
    //void createMenu1();

private:
    Ui::MainWindow *ui;
QMainWindow *mainWin;
//Spreadsheet *spreadsheet;
ArtistForm *addDataView;


QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuService;
    QMenu *menuHelp;
    QMenu *adminMenu;
    QMenu *searchMenu;
    QAction *newAction;

    QAction *exitAction;
    QAction *aboutUsAction;
    QAction *aboutCompanyQction;
    QAction *commandeAction;
    QAction *catalogageAction;
    QAction *pretAction;
    QAction *historyAction;
    QAction *adminAction;
    QAction *searchAction;
    //QAction *searchBookAction;
    
    QHBoxLayout *actionHBoxLayout;
    QHBoxLayout *welcomeHBoxLayout;
    QHBoxLayout *logoHBoxLayout;
    QVBoxLayout * mainVBoxLayout;
    
    QWidget *widget;
    
    QLabel *logolabel;
    QLabel *welcomelabel;
    static int counter;
    
    QComboBox *actionComboBox;
    
    QGroupBox *mainGrouBox;
    QGridLayout *mainGridLayout;
    
    hireBook *hireBookForm;
    historyDialog *historyWidget;
    bookCommand *bookCommandDialog;
    catalogageDialog *catalogueDialog;
    aboutUs *aboutUsDialog;
    adminDialog *dialog;
    searchDialog *searchBookDialog;
    int currentIndex;
    
public slots:
void establishConnection();
//void spreadsheetViewer();
void newEntryData();
void hireBookSlot();
void helpAboutUs();
void helpAboutCompany();
void commandeSlot();
void catalogageSlot();
void pretSlot();
void historySlot();
void raiseAdminSlot();
void searchBookSlot();

//void exitActionSlot();
};

#endif // MAINWINDOW_H
