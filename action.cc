#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
    MyRunAction *runAction = new MyRunAction(); //do run action for master thread
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(); //particle generator run action
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction(); //do run action for worker thread
    SetUserAction(runAction);
}