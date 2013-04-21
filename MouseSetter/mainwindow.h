#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>

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

public slots:
    void displayMouseInformationPopup();
    
private slots:
    void on_MouseInfoButton_clicked();
  //  void on_pushButton_4_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void on_actionAbout_triggered();
    void on_actionPreferences_triggered();
    void messageClicked();
    void exitApp();

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

    bool lastClose;

};

#endif // MAINWINDOW_H
