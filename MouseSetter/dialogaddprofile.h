#ifndef DIALOGADDPROFILE_H
#define DIALOGADDPROFILE_H

#include <QDialog>

namespace Ui {
class DialogAddProfile;
}

class DialogAddProfile : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddProfile(QWidget *parent = 0);
    ~DialogAddProfile();

public slots:
    virtual void accept();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddProfile *ui;
};

#endif // DIALOGADDPROFILE_H
