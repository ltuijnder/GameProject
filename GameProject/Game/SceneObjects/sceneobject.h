#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <iostream>

class SceneObject : public QObject, public QGraphicsItem
{
    Q_OBJECT

signals:

public slots:

protected:
    //Flags
    bool IsWritten;
    bool IsInit=0;// Important That is default value 0!!

public:
    // essential
    explicit SceneObject(QObject *parent = nullptr);

    // Variables
    int ObjectType;

    // Functions
    virtual void Init();
    // Write also virtual
    // Read also virtual
};

#endif // SCENEOBJECT_H
