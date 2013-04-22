#ifndef DIALOGMOUSEINFORMATION_H
#define DIALOGMOUSEINFORMATION_H

#include <QDialog>

namespace Ui {
class DialogMouseInformation;
}

class DialogMouseInformation : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMouseInformation(QWidget *parent = 0);
    ~DialogMouseInformation();
    Ui::DialogMouseInformation* getUI();
private:
    Ui::DialogMouseInformation *ui;
};

#endif // DIALOGMOUSEINFORMATION_H
