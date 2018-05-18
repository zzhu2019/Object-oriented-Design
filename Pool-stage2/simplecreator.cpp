#include "simplecreator.h"
#include "simpletable.h"
#include "simpleball.h"
#include "pockettable.h"
#include "QDebug"
#include <QJsonArray>
#include "QVector2D"
#include "compositeball.h"

unique_ptr<Table> SimpleCreator::makeTable(const QJsonObject &spec, int f) {//use default value if there is no value in config file
    //qDebug()<<"table default check:";
    int x=600, y=300;
    if(spec["size"] != QJsonValue::Undefined)
    {
        if(spec["size"].toObject()["x"] != QJsonValue::Null) x=spec["size"].toObject()["x"].toInt();
        if(spec["size"].toObject()["y"] != QJsonValue::Null) y=spec["size"].toObject()["y"].toInt();
    }
    tableHeight=y;
    tableWidth=x;

    QSize size(x, y);
    QSize size1(x, y);

    QColor colour("green");
    if(spec["colour"] != QJsonValue::Undefined) colour=spec["colour"].toString();

    double friction=0.01;
    if(spec["friction"] !=QJsonValue::Undefined ) friction=spec["friction"].toDouble();
    if(f == 1)//stage 1 wthout pockets
    {
        std::vector<unique_ptr<Pocket>> pockets;
        return unique_ptr<SimpleTable>(
            new SimpleTable(
                size, colour, friction, pockets
            )
        );
    }
    else//stage 2 with pockets
    {
        std::vector<unique_ptr<Pocket>> pockets;
        std::vector<unique_ptr<Pocket>> pockets1;
        std::vector<unique_ptr<Pocket>> pockets_empty;
        for (const auto& item : spec["pockets"].toArray())
        {
            QJsonObject poc=item.toObject();
            float radius=15;
            int x1=0, y1=0;
            if(poc["radius"] != QJsonValue::Null)
            {
                radius=poc["radius"].toDouble();
            }
            //else
                //qDebug()<<"Use default value!";
            if((poc["position"].toObject()["x"] != QJsonValue::Null) && (-radius < poc["position"].toObject()["x"].toDouble())&&(poc["position"].toObject()["x"].toDouble()<radius+x))
            {
                x1=poc["position"].toObject()["x"].toDouble();
            }
            else
            {
                qDebug()<<"Invalid pocket!";
                continue;
            }
            if((poc["position"].toObject()["y"] != QJsonValue::Null) && (-radius < poc["position"].toObject()["y"].toDouble())&&(poc["position"].toObject()["y"].toDouble()<radius+y))
            {
                y1=poc["position"].toObject()["y"].toDouble();
            }
            else
            {
                qDebug()<<"Invalid pocket!";
                continue;
            }
            QVector2D position1(x1, y1);
            pockets.push_back(unique_ptr<Pocket>(new Pocket(position1, radius)));
            pockets1.push_back(unique_ptr<Pocket>(new Pocket(position1, radius)));
        }
        return unique_ptr<PocketTable>(
                    new PocketTable(
                        unique_ptr<SimpleTable>(new SimpleTable(size, colour, friction, pockets_empty)), pockets, size1, friction, pockets1
                        )
                    );
    }
}

unique_ptr<Ball> SimpleCreator::makeBall(const QJsonObject &spec, int f) {//visibility toggle
    bool Delete=false;
    //qDebug()<<"ball default check:";
    double radius=10;
    if(spec["radius"] != QJsonValue::Undefined) radius=spec["radius"].toDouble();

    QColor colour("white");
    if(spec["colour"] != QJsonValue::Undefined) colour=spec["colour"].toString();

    double mass=1.0;
    if(spec["mass"] != QJsonValue::Undefined) mass=spec["mass"].toDouble();

    QVector2D position(0, 0);
    if(spec["position"] != QJsonValue::Undefined)
    {
        if(spec["position"].toObject()["x"] != QJsonValue::Null) position.setX(spec["position"].toObject()["x"].toDouble());
        if(spec["position"].toObject()["y"] != QJsonValue::Null) position.setY(spec["position"].toObject()["y"].toDouble());
    }
    if((position.x() == 0) || (position.y() == 0))
    {
        Delete = true;
    }
    else if(((position.x() < radius) || (position.x() > tableWidth-radius))
        || ((position.y() < radius) || (position.y() > tableHeight-radius)))
    {
        Delete = true;
    }

    QVector2D velocity(0, 0);
    if(spec["velocity"] != QJsonValue::Undefined)
    {
        if(spec["velocity"].toObject()["x"] != QJsonValue::Null) velocity.setX(spec["velocity"].toObject()["x"].toDouble());
        if(spec["velocity"].toObject()["y"] != QJsonValue::Null) velocity.setY(spec["velocity"].toObject()["y"].toDouble());
    }

    if(Delete)
    {
        qDebug()<<"Invalid ball";
    }

    if((f==1) && (Delete == false)) //stage 1 and the ball is valid
    {
        return unique_ptr<Ball>(
            new SimpleBall(
                radius, colour, mass, position, velocity, std::numeric_limits<double>::max(), false
            )
        );
    }
    else if ((f==2) && (Delete == false))//stage 2 and the ball is valid
    {
        double strength=std::numeric_limits<double>::max();
        if(spec["strength"] != QJsonValue::Undefined) strength=spec["strength"].toDouble();

        if(spec["balls"] != QJsonValue::Undefined)
        {
            vector<unique_ptr<Ball>> balls;
            for (const auto& item : spec["balls"].toArray())
            {
                balls.push_back(makeContainedBall(item.toObject(), colour, position));//use another make ball method to create contained ball
            }
            return unique_ptr<Ball>(
                new CompositeBall(
                    radius, mass, position, velocity, colour, strength, balls, true
                )
            );
        }
        else
        {
            return unique_ptr<Ball>(
                new SimpleBall(
                    radius, colour, mass, position, velocity, strength, false
                )
            );
        }
    }
}

unique_ptr<Ball> SimpleCreator::makeContainedBall(const QJsonObject &spec, const QColor &colour, const QVector2D &position)
{
    //qDebug()<<"make contained ball\n";
    double radius=10;
    if(spec["radius"] != QJsonValue::Undefined) radius=spec["radius"].toDouble();

    QString name=colour.name();
    QColor containedColor(name);
    if(spec["colour"] != QJsonValue::Undefined) containedColor=spec["colour"].toString();

    float x, y;
    x=position.x();
    y=position.y();
    QVector2D containedPos(x, y);
    if(spec["position"] != QJsonValue::Undefined)
    {
        if(spec["position"].toObject()["x"] != QJsonValue::Null)
            containedPos.setX(position.x()+spec["position"].toObject()["x"].toDouble());
        if(spec["position"].toObject()["y"] != QJsonValue::Null)
            containedPos.setY(position.y()+spec["position"].toObject()["y"].toDouble());
    }

    double mass=1.0;
    if(spec["mass"] != QJsonValue::Undefined) mass=spec["mass"].toDouble();

    double strength=std::numeric_limits<double>::max();
    if(spec["strength"] != QJsonValue::Undefined) strength=spec["strength"].toDouble();

    if (spec["balls"] != QJsonValue::Undefined)
    {
        vector<unique_ptr<Ball>> balls;
        for (const auto& item : spec["balls"].toArray())
        {
            balls.push_back(makeContainedBall(item.toObject(), containedColor, containedPos));//use another make ball method to create contained ball
        }
        return unique_ptr<Ball>(
            new CompositeBall(
                radius, mass, containedPos, QVector2D(0, 0), containedColor, strength, balls, true
            )
        );
    }
    else
    {
        return unique_ptr<Ball>(
            new SimpleBall(
                radius, containedColor, mass, containedPos, QVector2D(0, 0), strength, false
            )
        );
    }


}
