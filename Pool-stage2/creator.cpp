#include "creator.h"
#include "scenebuilder.h"//use builder to add table and balls
#include <QJsonArray>

unique_ptr<SceneManager> Creator::makeScene(const QJsonObject &spec) {
    SceneBuilder builder;//builder is director
    builder.setStageFlag(spec["stage2"].toBool());
    qDebug()<<"Stage2:"<<(spec["stage2"].toBool());
    if(spec["stage2"].toBool() == false)//stage 1 creator
    {
        builder.setTable(
            this->makeTable(spec["table"].toObject(), 1)
        );
        for (const auto& item : spec["balls"].toArray())
        {
            builder.addBall(
                this->makeBall(item.toObject(), 1)
            );
        }
    }
    else//stage 2 builder
    {
        builder.setTable(
            this->makeTable(spec["table"].toObject(), 2)
        );
        for (const auto& item : spec["balls"].toArray())
            builder.addBall(
                this->makeBall(item.toObject(), 2)
            );
    }
	return builder.build();
}
