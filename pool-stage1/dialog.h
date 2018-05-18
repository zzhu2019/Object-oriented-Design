/*!
  this file is for dialogue, the animation and uodate will take place here.
  It has 3 memeber variables and several functions.
*/
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include "product.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(poolGame *pg, QWidget *parent = 0);
    ~Dialog();

public slots:   //new
    void nextFrame();///< To update

protected:
    void paintEvent(QPaintEvent *event);///< To paint

private:
    Ui::Dialog *ui;///< ui pointer
    poolGame *m_pg;///< the pointer to the object of game itself
    int m_counter;///< time counter
};

#endif // DIALOG_H
