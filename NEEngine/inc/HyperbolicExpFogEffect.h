#pragma once
#include "Effect.h"

class Game;
class Texture;

class HyperbolicExpFogEffect :
    public Effect
{
public:
    HyperbolicExpFogEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);
};

