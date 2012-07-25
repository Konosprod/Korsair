#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWebKit>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

public slots:
    void addTabEmpty();
    void homePage();
    void previousPage();
    void nextPage();
    void closeTab();
    void refreshPage();
    void loadPage();
    void searchGoogle();
    void setTabTitle(QString);
    void newUrl(QUrl);
    void setnewWindowTitle(QString);
    void progressLoad(int);
    void beginLoad();
    void finishLoad(bool);
    void closeTabRequested(int);
    void tabChanged(int);
    void downloadContent(QNetworkRequest);
    void downloadUnsuportedContent(QNetworkReply*);
    void downloadFinished(QNetworkReply*);
    void editPref();

private:
    void setupAction();
    void setupMenu();
    void setupToolBar();
    void setupStatusBar();
    void createFirstTab();
    QWebView* currentPage();
    
private:
    Ui::mainWindow *ui;
    QTabWidget* m_Tab;
    QLineEdit* m_EntryUrl;
    QLineEdit* m_EntryGoogle;
    QProgressBar* m_ProgressBar;

    QAction* m_actionReturn;
    QAction* m_actionNext;
    QAction* m_actionLoad;
    QAction* m_actionHome;
    QAction* m_actionNewTab;
    QAction* m_actionCloseTab;
    QAction* m_actionRefresh;
    QAction* m_actionQuit;
    QAction* m_actionGoogle;
    QAction* m_actionEditPref;

    QSettings* settings;
};

#endif // MAINWINDOW_H
