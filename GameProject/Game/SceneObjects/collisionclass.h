#ifndef COLLISIONCLASS_H
#define COLLISIONCLASS_H

#include <QPointF>
#include "sceneobject.h"

class CollisionClass: public SceneObject
{
    Q_OBJECT

private:
    float width;
    float height;

    bool Penetrable;

protected:
    QPointF DiffPoint(CollisionClass *Object) const;

public:
    explicit CollisionClass(QObject *parent= nullptr);
    void InitCollision(float w, float h);

    float w() const;
    float h() const;
    void SetGeometry(float NewWidth,float NewHeight);
    void SetTeamCollision(int Team);// Delete this!!
    void SetPenetrability(bool Pen);

    bool IsPenetrable(int Team) const;
};

#endif // COLLISIONCLASS_H
