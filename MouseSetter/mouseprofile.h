#ifndef MOUSEPROFILE_H
#define MOUSEPROFILE_H

#include <QString>

class MouseProfile
{
public:
    MouseProfile();
    MouseProfile(int,int,int,int,QString);

    QString toString();
    int a0;
    int a1;
    int a2;
    int a3;
    QString name;
    QString folder;
};

#endif // MOUSEPROFILE_H
