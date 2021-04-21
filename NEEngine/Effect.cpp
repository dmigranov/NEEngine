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
	return m_magic;
}

bool Effect::IsInited()
{
	return m_isInited;
}

