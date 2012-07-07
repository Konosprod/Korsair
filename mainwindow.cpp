#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    QWidget* ecran = new QWidget(this);
    m_Tab = new QTabWidget(this);
    m_Tab->setMovable(true);
    m_Tab->setTabsClosable(true);
    connect(m_Tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabRequested(int)));
    connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    QVBoxLayout* layout = new QVBoxLayout(ecran);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_Tab);
    this->setCentralWidget(ecran);

    setupAction();
    setupMenu();
    setupToolBar();
    setupStatusBar();
    createFirstTab();
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::tabChanged(int)
{
    setnewWindowTitle(currentPage()->title());
    newUrl(currentPage()->url());
}

void mainWindow::closeTabRequested(int i)
{
    m_Tab->removeTab(i);
}

void mainWindow::setTabTitle(QString s)
{
    if(s.count() > 40)
    {
        m_Tab->setTabText(m_Tab->currentIndex(), s.left(40) + "...");
    }
    else
    {
        m_Tab->setTabText(m_Tab->currentIndex(), s);
    }
}

void mainWindow::newUrl(QUrl u)
{
    m_EntryUrl->setText(u.toString());
}


void mainWindow::setnewWindowTitle(QString s)
{
    if(s.count() > 40)
    {
        setWindowTitle("Korsair - " + s.left(40) + "...");
    }
    else
    {
        setWindowTitle("Korsair - " + s);
    }
}

void mainWindow::progressLoad(int i)
{
    m_ProgressBar->setValue(i);
}

void mainWindow::beginLoad()
{
    m_ProgressBar->setVisible(true);
}

void mainWindow::finishLoad(bool b)
{
    if(b)
    {
        m_ProgressBar->setVisible(false);
    }
}

void mainWindow::createFirstTab()
{
    addTabEmpty();
    homePage();
}

void mainWindow::addTabEmpty()
{
    QWidget* newTab = new QWidget(this);
    QWebView* wbv = new QWebView(newTab);
    QVBoxLayout* vb = new QVBoxLayout(newTab);
    vb->setContentsMargins(0, 0, 0, 0);
    vb->addWidget(wbv);
    newTab->setLayout(vb);
    int i = m_Tab->addTab(newTab, "Nouvel Onglet");
    m_Tab->setCurrentIndex(i);
    m_EntryUrl->setText("");
    m_EntryUrl->setFocus();

    connect(wbv, SIGNAL(loadStarted()), this, SLOT(beginLoad()));
    connect(wbv, SIGNAL(loadProgress(int)), this, SLOT(progressLoad(int)));
    connect(wbv, SIGNAL(loadFinished(bool)), this, SLOT(finishLoad(bool)));
    connect(wbv, SIGNAL(titleChanged(QString)), this, SLOT(setTabTitle(QString)));
    connect(wbv, SIGNAL(titleChanged(QString)), this, SLOT(setnewWindowTitle(QString)));
    connect(wbv, SIGNAL(urlChanged(QUrl)), this, SLOT(newUrl(QUrl)));
}

QWebView* mainWindow::currentPage()
{
    return m_Tab->currentWidget()->findChild<QWebView*>();
}

void mainWindow::previousPage()
{
    if(currentPage() != 0)
    {
        currentPage()->back();
    }
}

void mainWindow::nextPage()
{
    if(currentPage() != 0)
    {
        currentPage()->forward();
    }
}

void mainWindow::homePage()
{
    if(currentPage() != 0)
    {
        currentPage()->setUrl(QUrl("http://www.google.fr"));
    }
}

void mainWindow::refreshPage()
{
    if(currentPage() != 0)
    {
        currentPage()->reload();
    }
}

void mainWindow::closeTab()
{
    if(m_Tab->count() > 0)
    {
        m_Tab->removeTab(m_Tab->currentIndex());
    }
}

void mainWindow::setupStatusBar()
{
    m_ProgressBar = new QProgressBar(this);
    m_ProgressBar->setVisible(false);
    ui->statusbar->addWidget(m_ProgressBar);
}

void mainWindow::loadPage()
{
    QString url;

    if(currentPage() != 0)
    {
        if(m_EntryUrl->text().isEmpty())
        {
            return;
        }
        else
        {
            if(!m_EntryUrl->text().contains("http://") && !m_EntryUrl->text().contains("https://"))
            {
                url += "http://" + m_EntryUrl->text();
            }
            else
            {
                url = m_EntryUrl->text();
            }
            currentPage()->setUrl(QUrl(url));
            m_EntryUrl->setText(url);
        }
    }
}

void mainWindow::searchGoogle()
{
    QString url;

    if(currentPage() != 0)
    {
        if(m_EntryUrl->text().isEmpty())
        {
            return;
        }
        else
        {
            if(!m_EntryGoogle->text().isEmpty())
            {
                url += "http://www.google.fr/search?q=" + m_EntryGoogle->text();
            }
            currentPage()->setUrl(QUrl(url));
            m_EntryUrl->setText(url);
        }
    }
}

void mainWindow::setupAction()
{
    m_actionReturn = new QAction("Précédent", this);
    m_actionReturn->setShortcut(QKeySequence("Ctrl+P"));
    m_actionReturn->setIcon(QIcon(":/ressources/iReturn"));
    m_actionReturn->setIconVisibleInMenu(true);
    connect(m_actionReturn, SIGNAL(triggered()), this, SLOT(previousPage()));

    m_actionNext = new QAction("Suivant", this);
    m_actionNext->setShortcut(QKeySequence("Ctrl+N"));
    m_actionNext->setIcon(QIcon(":/ressources/iNext"));
    m_actionNext->setIconVisibleInMenu(true);
    connect(m_actionNext, SIGNAL(triggered()), this, SLOT(nextPage()));

    m_actionLoad = new QAction("Aller", this);
    m_actionLoad->setIcon(QIcon(":/ressources/iLoad"));
    connect(m_actionLoad, SIGNAL(triggered()), this, SLOT(loadPage()));

    m_actionGoogle = new QAction("Google", this);
    m_actionGoogle->setIcon(QIcon(":ressources/iLoad"));
    connect(m_actionGoogle, SIGNAL(triggered()), this, SLOT(searchGoogle()));

    m_actionHome = new QAction("Page d'accueil", this);
    m_actionHome->setShortcut(QKeySequence("Ctrl+H"));
    m_actionHome->setIcon(QIcon(":/ressources/iHome"));
    m_actionHome->setIconVisibleInMenu(true);
    connect(m_actionHome, SIGNAL(triggered()), this, SLOT(homePage()));

    m_actionNewTab = new QAction("Nouvel onglet", this);
    m_actionNewTab->setShortcut(QKeySequence("Ctrl+T"));
    connect(m_actionNewTab, SIGNAL(triggered()), this, SLOT(addTabEmpty()));

    m_actionCloseTab = new QAction("Fermer l'onget", this);
    m_actionCloseTab->setShortcut(QKeySequence("Ctrl+W"));
    connect(m_actionCloseTab, SIGNAL(triggered()), this, SLOT(closeTab()));

    m_actionRefresh = new QAction("Rafraichir", this);
    m_actionRefresh->setShortcut(QKeySequence("Ctrl+R"));
    m_actionRefresh->setIcon(QIcon(":/ressources/iRefresh"));
    connect(m_actionRefresh, SIGNAL(triggered()), this, SLOT(refreshPage()));

    m_actionQuit = new QAction("Quitter", this);
    m_actionQuit->setShortcut(QKeySequence("Ctrl+Q"));

}

void mainWindow::setupMenu()
{
    QMenu* menuFichier = menuBar()->addMenu("Fichier");
    QMenu* menuNavigation = menuBar()->addMenu("Navigation");

    menuFichier->addAction(m_actionNewTab);
    menuFichier->addAction(m_actionCloseTab);
    menuFichier->addSeparator();
    menuFichier->addAction(m_actionQuit);

    menuNavigation->addAction(m_actionReturn);
    menuNavigation->addAction(m_actionNext);
    menuNavigation->addAction(m_actionHome);
}

void mainWindow::setupToolBar()
{
    m_EntryUrl = new QLineEdit(this);
    m_EntryGoogle = new QLineEdit(this);
    ui->toolBar->addAction(m_actionHome);
    ui->toolBar->addAction(m_actionReturn);
    ui->toolBar->addAction(m_actionNext);
    ui->toolBar->addAction(m_actionRefresh);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(m_EntryUrl);
    ui->toolBar->addAction(m_actionLoad);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(m_EntryGoogle);
    ui->toolBar->addAction(m_actionGoogle);

    connect(m_EntryUrl, SIGNAL(returnPressed()), this, SLOT(loadPage()));
    connect(m_EntryGoogle, SIGNAL(returnPressed()), this, SLOT(searchGoogle()));
}
