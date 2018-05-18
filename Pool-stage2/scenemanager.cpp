#include "scenemanager.h"
#include "math.h"
#include "QMouseEvent"
#include "iostream"

void collideBalls(Ball&, Ball&);
void collideTable(const Table&, Ball&);
QVector2D isTouching(const Ball&, const Ball&);
QVector2D isTouching(const Table&, const Ball&);
bool isEncompassed(const Pocket&, const Ball&);
bool isBroke(Ball&, QVector2D&);



SceneManager::SceneManager(unique_ptr<Table> poolTable, vector<unique_ptr<Ball>>& initBalls, bool f)
: table(std::move(poolTable)), balls(std::move(initBalls)), offset(20, 20), stage2(f) {}

void SceneManager::draw(QPainter& painter) const {
	painter.translate(offset);
    this->table->draw(painter);
	for (const auto& item: this->balls) {
        item->draw(painter);
	}
	painter.translate(-offset);
}

void SceneManager::setStage2Bool(bool f)
{
    stage2=f;//it is not a stage two table
}

bool SceneManager::getFlag() const
{
    return this->stage2;
}

void SceneManager::setCueBallV(QVector2D vel)
{
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a)
        {
            Ball& ballA = **a;
            if ((ballA.getColour() == "#ffffff") && (ballA.velocity.isNull()) &&(stage2 == true))// first white ball and at rest and it is stage 2
            {
                ballA.velocity.setX(vel.x());
                ballA.velocity.setY(vel.y());
                break;
            }
        }
}

void SceneManager::resetBallV()
{
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a)
    {
        Ball& ballA = **a;
        if(abs(ballA.velocity.x()) <= 0.01)
        {
            ballA.velocity.setX(0.f);
        }
        if(abs(ballA.velocity.y()) <= 0.01)
        {
            ballA.velocity.setY(0.f);
        }
    }
}

QSize SceneManager::veiwPort() const {
	return this->table->dimension + QSize(this->offset.x(), this->offset.y())*2;
}

//delete the item after iteration which ball should be deleted and added into balls vector.
//add a flag named "shouldBreak"
//make modification after interation
void SceneManager::tick(float dtime) {
    int num = 0;
    int length=this->balls.size();
    bool delete_flag=false;
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a) {//loop for ball
        Ball& ballA = **a;//set ballA's address to an object
        collideTable(*this->table, ballA);
		for (auto b = a + 1; b != this->balls.end(); ++b) {
            collideBalls(ballA, **b);
		}

        for (auto p = this->table->pockets.begin(); p != this->table->pockets.end(); ++p) {//check ball and pocket encompassment
            Pocket& PocketA = **p;
            bool flag = isEncompassed(PocketA, ballA);
            if (flag)
            {
                qDebug()<<"delete a ball due to fall";
                if(num==(length-1))
                {
                    this->balls.pop_back();
                    a--;
                }
                else
                    this->balls.erase(balls.begin()+num);
                delete_flag = true; // if the ball needs to be deleted, mark it as 'delete', the delete it after the interation
                break;
            }
        }
        if(delete_flag)
        {
            delete_flag=false;
            continue;
        }
        else
            num++;

		ballA.position += ballA.velocity * dtime;
        if(ballA.isContained)
        {
            ballA.changePforContained(ballA.velocity * dtime);
        }
		ballA.velocity -= ballA.velocity.normalized() * dtime * this->table->surface_friction;
	}
    std::vector<int> index;
    int in=0;
    for (auto a = this->balls.begin(); a != this->balls.end(); ++a, ++in)
    {
        Ball& ballA = **a;
        if(ballA.isRemove==true)
        {
            index.push_back(in);
        }
    }
    if(index.size())
    {
        for(auto n = index.begin(); n != index.end(); ++n)
        {
            int num=*n;
            (this->balls[num])->moveOut(this->balls);
            this->balls.erase(balls.begin()+num);
            qDebug()<<"delete a ball due to break";
        }
    }

    this->resetBallV();
    //make modification here

}

void collideTable(const Table& table, Ball& ball) {

	auto collision = isTouching(table, ball);

	if (QVector2D::dotProduct(collision, ball.velocity) < 0)
		return;

	if (collision.x())
    {
        if((ball.isContained) || ((!ball.isContained) && (ball.getStrength() != std::numeric_limits<double>::max())))
        {
            float delX;
            delX=abs(2*ball.velocity.x());
            QVector2D delV(delX, 0.0f);
            isBroke(ball, delV);
            //MOVE the new balls into ball vector
        }
		ball.velocity *= QVector2D(-1, 1);
    }
	else if (collision.y())
    {
        if((ball.isContained) || ((!ball.isContained) && (ball.getStrength() != std::numeric_limits<double>::max())))
        {
            float delY;
            delY=abs(2*ball.velocity.y());
            QVector2D delV(delY, 0.0f);
            isBroke(ball, delV);
            //MOVE the new balls into ball vector
        }
		ball.velocity *= QVector2D(1, -1);
    }
}

void collideBalls(Ball& ballA, Ball& ballB) {// not a good idea to use reference
	// SOURCE : ASSIGNMENT SPEC
	auto collision = isTouching(ballA, ballB);
	if (collision == NULL_2D) return;

    float mr = ballB.getMass() / ballA.getMass();
	double pa = QVector2D::dotProduct(collision, ballA.velocity);
	double pb = QVector2D::dotProduct(collision, ballB.velocity);

	if (pa <= 0 && pb >= 0) return;

	double a = -(mr + 1);
	double b = 2*(mr * pb + pa);
	double c = -((mr - 1)*pb*pb + 2*pa*pb);
	double disc = sqrt(b*b - 4*a*c);
	double root = (-b + disc)/(2*a);
	if (root - pb < 0.01) {
		root = (-b - disc)/(2*a);
	}

    //to be done
    if((ballA.isContained) || ((!ballA.isContained) && (ballA.getStrength() != std::numeric_limits<double>::max())))
    {
        QVector2D delVA(mr * (pb - root) * collision);
        isBroke(ballA, delVA);
        //MOVE the new balls into ball vector
    }
    if((ballB.isContained) || ((!ballB.isContained) && (ballB.getStrength() != std::numeric_limits<double>::max())))
    {
        QVector2D delVB((root - pb) * collision);
        isBroke(ballB, delVB);
        //MOVE the new balls into ball vector
    }


	ballA.velocity += mr * (pb - root) * collision;
	ballB.velocity += (root - pb) * collision;
}

QVector2D isTouching(const Ball& ballA, const Ball& ballB) {
	auto collision = ballB.position - ballA.position;
	if (collision.length() <= ballA.radius + ballB.radius)
		return collision.normalized();
	else
		return NULL_2D;
}

QVector2D isTouching(const Table& table, const Ball& ball) {
	if (ball.position.x() <= ball.radius)
		return QVector2D(-1, 0);
	else if (ball.position.y() <= ball.radius)
		return QVector2D(0, -1);
	else if (ball.position.x() + ball.radius >= table.dimension.width())
		return QVector2D(1, 0);
	else if (ball.position.y() + ball.radius >= table.dimension.height())
		return QVector2D(0, 1);
	else
		return NULL_2D;
}

bool isEncompassed(const Pocket& pocket, const Ball& ball)//if encompassment
{
    auto distance = pocket.position - ball.position;
    if (pocket.radius - distance.length() >= ball.radius)
        return true;
    else
        return false;
}

bool isBroke(Ball& ball, QVector2D& delV)
{
    //from assignment spec
    if(ball.isContained) //has conatiend ball
    {
        float energyOfCollision = ball.getMass()*delV.lengthSquared();
        qDebug()<<"strength: "<<ball.getStrength()<<" : "<<"energy: "<<energyOfCollision;
        if(ball.getStrength() < energyOfCollision)
        {
            ball.isRemove=true;
            float energyPerBall = energyOfCollision/ball.getContainedBallNumber();
            QVector2D pointOfCollision((-delV.normalized())*ball.radius);
            ball.changeVforContained(ball.velocity, energyPerBall, pointOfCollision);
        }
    }
    else if((!ball.isContained) && (ball.getStrength() != std::numeric_limits<double>::max()))//dont have contained ball
    {
        float energyOfCollision = ball.getMass()*delV.lengthSquared();
        qDebug()<<ball.getStrength()<<energyOfCollision;
        if(ball.getStrength() < energyOfCollision)
        {
            ball.isRemove=true;
        }
    }
}


