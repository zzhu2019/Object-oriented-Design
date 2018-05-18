#include "dialog.h"
#include <QApplication>
#include "concretefactory.h"
#include "concretebuilder.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "iostream"
#include "QStringList"
#include "string"
using namespace std;

class director{
    //principles for creating the pool
    manufacturer *m_builder;
public:
    ~director()
    {
        //cannot delete otherwise exited abnormally
    }
    director(manufacturer *builder) : m_builder(builder) {}
    poolGame * construct(int n, poolTable t_table, vector<poolBall> t_balls)
    {
        poolGame * game = m_builder->getPool();
        game->addTable(m_builder->buildTable(t_table.getxsize(), t_table.getysize(), t_table.getcolor(), t_table.getfriction()));
        for(int i = 0; i < n; i++)
        {
            game->addBall(m_builder->buildBall(t_balls[i].getcoordinate(), t_balls[i].getradius(), t_balls[i].getcolor(),
                                              t_balls[i].getmass(), t_balls[i].getvelocity()));
        }
        return game;
    }

};

int main(int argc, char *argv[])
{
    vector<poolBall> t_balls;
    QString config;
    QFile file;
    file.setFileName("/Users/zhuzihan/Desktop/INFO3220 Object Oriented Design/project/build-pool-Desktop_Qt_5_9_4_clang_64bit-Debug/config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    config = file.readAll();
    file.close();
    QJsonDocument cf = QJsonDocument::fromJson(config.toUtf8());

    QJsonObject jsonObject = cf.object();
    QJsonObject jsonObject3 = jsonObject["table"].toObject();
    string tableColor = (jsonObject3["colour"].toString()).toStdString();
    QJsonObject jsonObject4 = jsonObject3["size"].toObject();
    double xsize = (jsonObject4["x"].toDouble());
    double ysize = (jsonObject4["y"].toDouble());
    double fri  = (jsonObject3["friction"].toDouble());
    poolTable t_table(xsize, ysize, tableColor, fri);

    QJsonArray jsonArray = jsonObject["balls"].toArray();
    foreach (const QJsonValue & value, jsonArray)
    {
        double mass, radius, xposition, yposition, xvelocity, yvelocity;
        string color;
        QJsonObject obj = value.toObject();
        color = (obj["colour"].toString()).toStdString();
        mass = (obj["mass"].toDouble());
        radius = (obj["radius"].toDouble());

        QJsonObject jsonObject1 = obj["position"].toObject();
        QJsonObject jsonObject2 = obj["velocity"].toObject();
        xposition = (jsonObject1["x"].toDouble());
        yposition = (jsonObject1["y"].toDouble());
        xvelocity = (jsonObject2["x"].toDouble());
        yvelocity = (jsonObject2["y"].toDouble());

        Coordinate c(xposition, yposition, 0);
        Velocity v(xvelocity, yvelocity);
        poolBall ball(c, radius, color, mass, v);        v.changeXVelocity(23);
        ball.getvelocity().changeXDirection();
        //qDebug() << v.getXVelocity();
        //Coordinate coordinate, double radius, string color, double mass, Velocity velocity
        t_balls.push_back(ball);
    }

    //to be done get xsize, ysize, table color, and mass, radius, ball color, coordinate, velocity from each balls.
    int n = t_balls.size();

    poolManufacturer pm;
    director dir(&pm);
    //director combine table and balls into an default pool

    poolGame * pgPointer = dir.construct(n, t_table, t_balls);//what I get so far
    //concrete builder finalise the process

    QApplication a(argc, argv);
    Dialog w(pgPointer);
    w.show();

    t_balls.clear();
    return a.exec();
}
