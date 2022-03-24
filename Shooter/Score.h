#pragma once
#include "IObserver.h"
class Score :
    public IObserver
{
public:
    Score();
    ~Score();

    void OnNotify(int idEvent);

private:
    int scorePts;
};