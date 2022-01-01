#include "CoreTime.h"
#include <QDebug>

CoreTime::CoreTime()
{
    timer = new QElapsedTimer;
}
void CoreTime::update(){

}
float CoreTime::GetDeltaTime(){
    return deltaTime;
}
QElapsedTimer* CoreTime::GetTimer(){
    return timer;
}
void CoreTime::SetDeltaTime(float dt){
    deltaTime = dt;
}
