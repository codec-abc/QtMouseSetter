#include "mouseprofile.h"

MouseProfile::MouseProfile()
{
}

MouseProfile::MouseProfile(int a0in,int a1in,int a2in,int a3in,QString namein)
    :
      a0(a0in),
      a1(a1in),
      a2(a2in),
      a3(a3in),
      name(namein)
{

}


QString MouseProfile::toString()
{
    return QString( "" + QString::number(a0) + " " + QString::number(a1)+ " " +QString::number(a2) + " " + QString::number(a3) + " " +name );
}
