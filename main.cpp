#include <QApplication>
#include<QSplashScreen>
#include "mainwindow.h"
#include"connexion.h"
int main(int argc, char *argv[])
{
QApplication app(argc, argv);
QString database = QString("librarydatabase.db");
createConnexion(database);
QSplashScreen *splash = new QSplashScreen;
splash->setPixmap(QPixmap(":/images/splash.png"));
splash->show();

Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
splash->showMessage(QObject::tr("Setting up the main window..."),
topRight, Qt::white);
//MainWindow mainWin;
splash->showMessage(QObject::tr("Loading modules..."),
topRight, Qt::white);
//loadModules();
splash->showMessage(QObject::tr("Establishing connections..."),
topRight, Qt::white);
//establishConnections();




MainWindow *mainWin = new MainWindow;

/*foreach (QWidget *win, QApplication::topLevelWidgets()) {
if (MainWindow *mainWin = qobject_cast<MainWindow *>(win))
mainWin->updateRecentFileActions();


}*/
splash->finish(mainWin);
mainWin->show();
delete splash;
return app.exec();
}
