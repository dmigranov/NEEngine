#pragma once

#include "Geometries/SphericalEllipticGeometry.h"

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);


const int friedmann_w = 300, friedmann_h = 90;