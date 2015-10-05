/* 
 * File:   testForm.h
 * Author: albarral
 *
 * Created on February 23, 2015, 6:07 PM
 */

#ifndef _TESTFORM_H
#define	_TESTFORM_H

#include "ui_testForm.h"

class testForm : public QDialog {
    Q_OBJECT
public:
    testForm();
    virtual ~testForm();
private:
    Ui::testForm widget;
};

#endif	/* _TESTFORM_H */
