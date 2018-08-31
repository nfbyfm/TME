#include "mapage.h"

MAPage::MAPage(QObject *parent) : QObject(parent)
{
    //set Default-values (A4)
    this->width = 210;
    this->height = 297;
}

void MAPage::setHeight(float h){this->height = h;}
void MAPage::setWidht(float w){this->width = w;}

float MAPage::getWidth(){return this->width;}
float MAPage::getHeight(){return this->height;}
