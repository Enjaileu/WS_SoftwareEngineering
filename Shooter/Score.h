#pragma once
#include "IObserver.h"
class Score :
    public IObserver
{
public:
    Score();
    ~Score();

    void OnNotify(int idEvent);
    int SetScore(int value) { scorePts = value; }

private:
    int scorePts;
};

