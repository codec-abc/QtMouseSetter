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

public slots:
    void displayMouseInformationPopup();
    
private slots:
    void on_MouseInfoButton_clicked();
    void on_pushButton_4_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);

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

    QSettings settings;

    Ui::MainWindow *ui;
    QString string1;

};

#endif // MAINWINDOW_H
