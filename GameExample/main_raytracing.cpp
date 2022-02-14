#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

double RayTraceSphere(SphericalTransformComponent * pTransform) {
    auto pos_world = pTransform->GetSphericalPosition();
    auto pos = Vector4::Transform(pos_world, view); //pos_view
    auto pos_w = pos.w;
    auto posProj_4D = Vector4(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w, 1.f);
    auto posProj = Vector3(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w);

    Vector3 centerToBeginning = posProj - rayStart; // rayStart = 0, so centerToBeginning = posProj
    double lenToCenterOfSphere_sq = pow(centerToBeginning.x, 2) + pow(centerToBeginning.y, 2) + pow(centerToBeginning.z, 2);

    // inside this sphere
    if (lenToCenterOfSphere_sq < r_projected_sq)
    {
        std::cout << "inside" << std::endl;
        continue;   //camera is inside of this sphere so no need
    }

    // ray starts outside this sphere
    float lenClosestPoint = centerToBeginning.Dot(direction);  //расстояние от начала луча до ближайшей к центру сферы точки луча
    //std::cout << lenClosestPoint << std::endl;
    if (lenClosestPoint < 0)
    {
        continue; //ray doesn't intersect
    }

    double thc_sq = r_projected_sq - lenToCenterOfSphere_sq + lenClosestPoint * lenClosestPoint;
    if (thc_sq < 0)
    {
        continue; //ray doesn't intersect
    }

    double thc = sqrt(thc_sq);
    double t = lenClosestPoint - thc; //t is the distance to the intersection point

}