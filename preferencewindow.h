#ifndef preferenceWindow_H
#define preferenceWindow_H

#include <QDialog>
#include <QtGui>
#include <QSettings>

namespace Ui {
class preferenceWindow;
}

class preferenceWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit preferenceWindow(QWidget *parent, QString url = "");
    ~preferenceWindow();

public slots:
    void setDownloadPath();
    void setHome();
    void resetAll();
    QString homePath();
    QString downloadPath();
    
private:
    Ui::preferenceWindow *ui;
    QSettings* settings;
    QString currentUrl;
    QString download;
    QString home;
};

#endif // preferenceWindow_H
