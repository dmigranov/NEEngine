#pragma once
#include "Sound.h"
class DynamicSound :
    public Sound
{
public:
    DynamicSound(std::function<void(int16_t*, int, int)> generateFunction);
    ~DynamicSound();
private:

};

