#include "preferencewindow.h"
#include "ui_preferencewindow.h"

preferenceWindow::preferenceWindow(QWidget *parent, QString url) : QDialog(parent),
    ui(new Ui::preferenceWindow)
{
    ui->setupUi(this);

    settings = new QSettings("Tartine", "Korsair", this);

    ui->lineDownload->setText(settings->value("defaultDownloadPath", QDir::homePath()).toString());
    ui->lineHome->setText(settings->value("defaultHomePage", "http://www.google.com/").toString());

    currentUrl = url;

    connect(ui->buttonDownload, SIGNAL(clicked()), this, SLOT(setDownloadPath()));
    connect(ui->buttonHome, SIGNAL(clicked()), this, SLOT(setHome()));
    connect(ui->buttonReset, SIGNAL(clicked()), this, SLOT(resetAll()));
}

preferenceWindow::~preferenceWindow()
{
    delete ui;
}

void preferenceWindow::setDownloadPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Dossier de téléchargements", QDir::homePath());

    if(!dir.isEmpty())
    {
        ui->lineDownload->setText(dir);
    }
}

void preferenceWindow::setHome()
{
    ui->lineHome->setText(currentUrl);
}

void preferenceWindow::resetAll()
{
    ui->lineDownload->setText(QDir::homePath());
    ui->lineHome->setText("http://www.google.com/");
}

QString preferenceWindow::homePath()
{
    return ui->lineHome->text();
}

QString preferenceWindow::downloadPath()
{
    return ui->lineDownload->text();
}
