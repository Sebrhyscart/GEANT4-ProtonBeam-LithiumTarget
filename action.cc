#include "action.hh"

MyActionInitialization::MyActionInitialization()
{} //constructor (no additional action is required => empty)

MyActionInitialization::~MyActionInitialization()
{} //destructor (no additional action is required => empty)

void MyActionInitialization::BuildForMaster() const
{
    //=========================================================================================================================
    //this function initilizes all user actions taken in the master thread
    //=========================================================================================================================

    MyRunAction *runAction = new MyRunAction(); //We only need a run action, to control what happens before/after each run
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
    //=========================================================================================================================
    //this function initilizes all user actions taken in the worker threads
    //=========================================================================================================================

    MyPrimaryGenerator *generator = new MyPrimaryGenerator(); //initilize the Primary Generator here!
    SetUserAction(generator);
    //** generating primary particles only happens in the worker threads

    MyRunAction *runAction = new MyRunAction(); //run action to control what happens before/after each run for worker threads
    SetUserAction(runAction);
}