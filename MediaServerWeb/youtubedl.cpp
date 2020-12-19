#include "youtubedl.h"
#include <QDebug>
#include "dataobjectmodel.h"
#include <qqmlcontext.h>

Youtubedl::Youtubedl(QObject *parent) : QObject(parent)
{

}
void Youtubedl::test(QObject *list)
{
    qDebug() << "hello";
    AnimalModel model;
    model.addAnimal(Animal("Wolf", "Medium"));
    model.addAnimal(Animal("Polar bear", "Large"));
    model.addAnimal(Animal("Quoll", "Small"));
    model.addAnimal(Animal("Quoll", "Small"));
    model.addAnimal(Animal("Quoll", "Small"));
    model.addAnimal(Animal("Quoll", "Small"));

    QQmlContext *ctxt = Youtubedl::mainView->rootContext();
    ctxt->setContextProperty("myModel", &model);
}
