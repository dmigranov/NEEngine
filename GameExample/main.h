#pragma once

#include "Geometries/SphericalEllipticGeometry.h"

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);

void UpdateFriedmannWindow(double time);
void DrawFriedmannPoint(HDC hdc);

double RayTraceSphere(SphericalTransformComponent * pTransform, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view);


const int friedmann_w = 300, friedmann_h = 90;