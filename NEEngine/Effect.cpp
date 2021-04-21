#include "pch.h"
#include "Effect.h"


Effect::Effect()
{
}

Effect::~Effect()
{
	//todo
}

std::string Effect::GetName()
{
	return magic;
}

bool Effect::IsInited()
{
	return m_isInited;
}

