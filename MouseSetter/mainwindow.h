#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>
#include "mouseprofile.h"
#include <vector>
#include <utility>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSettings* getSetting();
    void addProfile(MouseProfile);
    static QString const profilePrefix;

public slots:
    void displayMouseInformationPopup();
    void updateProfiles();
    void applyProfileFromIndex(int i);
    
private slots:
    void on_MouseInfoButton_clicked();
  //  void on_pushButton_4_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void on_actionAbout_triggered();
    void on_actionPreferences_triggered();
    void messageClicked();
    void exitApp();

    void on_pushButtonAddProfile_clicked();
    void setButtonsState(bool state);

private:
    void createActions();
    void createTrayIcon();
    void setIcon();
    void closeEvent(QCloseEvent *); // Overriding the window's close event

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QMenu *subMenuTrayIcon;

    QAction *open;
    QAction *close;

    QSettings* settings;

    Ui::MainWindow *ui;
    QString string1;

    std::vector<std::pair<MouseProfile,QAction*> > mouseProfileAndAction;

    bool lastClose;
    QSignalMapper* signalMapper;

};

#endif // MAINWINDOW_H
