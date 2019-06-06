#ifndef COLLISIONCLASS_H
#define COLLISIONCLASS_H

#include <QPointF>
#include "sceneobject.h"

class CollisionClass
{


private:
    float width;
    float height;

    bool Penetrable;
    int TeamCollision;

protected:
    QPointF DiffPoint(SceneObject *This,CollisionClass *ThisCol, SceneObject *Other,CollisionClass *OtherCol) const;

public:
    CollisionClass();
    void InitCollision(float w, float h, int team);

    float w() const;
    float h() const;
    void SetGeometry(float NewWidth,float NewHeight);
    void SetTeamCollision(int Team);

    bool IsPenetrable(int Team) const;
};

#endif // COLLISIONCLASS_H
