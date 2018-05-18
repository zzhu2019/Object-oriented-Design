#include "dialog.h"
#include "ui_dialog.h"
#include "QPainter"
#include "string"
#include "iostream"
#include "QString"

Dialog::Dialog(poolGame *pg, QWidget *parent):
    QDialog(parent),
    ui(new Ui::Dialog),
    m_pg(pg),
    m_counter(0)
{
    ui->setupUi(this);
    int x, y;
    x = int(m_pg->getpooltable()->getxsize());
    y = int(m_pg->getpooltable()->getysize());
    string color = m_pg->getpooltable()->getcolor();
    string command = "background-color: "+color+";";
    QString Qcommand = QString::fromStdString(command);
    this->resize(x, y);//green: #328930 ,#C36241
    this->setStyleSheet(Qcommand);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);
}

void Dialog::nextFrame()
{
    update();
}

void Dialog::paintEvent(QPaintEvent *event)
{
    //to be done：

    QPainter painter(this);
    int n = m_pg->getpoolBalls().size();
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1 ; j < n; j++)
        {
            if(m_pg->isBallCollision(m_pg->getOnePoolball(i), m_pg->getOnePoolball(j)))
            {
                m_pg->CollisionBall(m_pg->getOnePoolball(i), m_pg->getOnePoolball(j));
            }
        }
        m_pg->getOnePoolball(i)->isCollisionWall(painter, m_counter, m_pg->getpooltable()->getxsize(), m_pg->getpooltable()->getysize(), m_pg->getpooltable()->getfriction());
    }
//    for (poolBall* i : m_pg->getpoolBalls())；
//    {
//        i->isCollisionWall(painter, m_counter, m_pg->getpooltable()->getxsize(), m_pg->getpooltable()->getysize(), m_pg->getpooltable()->getfriction());
//    }
    m_counter++;
}

Dialog::~Dialog()
{
    delete m_pg;
    delete ui;
}
