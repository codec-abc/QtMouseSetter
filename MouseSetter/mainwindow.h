#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    QString string1;
};

#endif // MAINWINDOW_H
