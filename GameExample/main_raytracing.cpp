#pragma once

#include "main.h"
#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

double RayTraceSpherePos(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, 
    DirectX::SimpleMath::Vector3 direction, 
    DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_projected_sq) {
    auto pos_world = sphericalPosition;
    auto pos = Vector4::Transform(pos_world, view); //pos_view

    if (pos.z < 0)
        return -1;

    auto pos_w = pos.w;
    //auto posProj_4D = Vector4(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w, 1.f);
    //auto posProj = Vector3(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w);

    auto posProj_4D = Vector4::Transform(pos, proj);
    auto posProj = Vector3(posProj_4D.x / posProj_4D.w, posProj_4D.y / posProj_4D.w, posProj_4D.z / posProj_4D.w);

    Vector3 centerToBeginning = posProj - rayStart; // rayStart = 0, so centerToBeginning = posProj
    double lenToCenterOfSphere_sq = pow(centerToBeginning.x, 2) + pow(centerToBeginning.y, 2) + pow(centerToBeginning.z, 2);
    
    // inside this sphere
    if (lenToCenterOfSphere_sq < r_projected_sq) 
    {
        return -1;   //camera is inside of this sphere so no need
    }

    // ray starts outside this sphere
    float lenClosestPoint = centerToBeginning.Dot(direction);  //расстояние от начала луча до ближайшей к центру сферы точки луча
    if (lenClosestPoint < 0)
    {
        return -1; //ray doesn't intersect
    }

    //todo: посмотреть заново радиус
    double thc_sq = r_projected_sq - lenToCenterOfSphere_sq + lenClosestPoint * lenClosestPoint;
    if (thc_sq < 0)
    {
        return -1; //ray doesn't intersect
    }


    double thc = sqrt(thc_sq);
    double t = lenClosestPoint - thc; //t is the distance to the intersection point
    return t;
}


double RayTraceSphereNeg(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq) {
    auto pos_world = sphericalPosition;
    auto pos = Vector4::Transform(pos_world, view); //pos_view
    auto pos_w = -pos.w;
    auto posProj_4D = Vector4(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w, 1.f);
    auto posProj = Vector3(pos.x / pos_w, pos.y / pos_w, pos.z / pos_w);

    Vector3 centerToBeginning = posProj - rayStart; // rayStart = 0, so centerToBeginning = posProj
    double lenToCenterOfSphere_sq = pow(centerToBeginning.x, 2) + pow(centerToBeginning.y, 2) + pow(centerToBeginning.z, 2);

    // inside this sphere
    if (lenToCenterOfSphere_sq < r_projected_sq)
    {
        std::cout << "inside" << std::endl;
        return -1;   //camera is inside of this sphere so no need
    }

    // ray starts outside this sphere
    float lenClosestPoint = centerToBeginning.Dot(direction);  //расстояние от начала луча до ближайшей к центру сферы точки луча
    //std::cout << lenClosestPoint << std::endl;
    if (lenClosestPoint < 0)
    {
        return -1; //ray doesn't intersect
    }

    double thc_sq = r_projected_sq - lenToCenterOfSphere_sq + lenClosestPoint * lenClosestPoint;
    if (thc_sq < 0)
    {
        return -1; //ray doesn't intersect
    }

    double thc = sqrt(thc_sq);
    double t = lenClosestPoint - thc; //t is the distance to the intersection point
    return t;
}

double RayTraceSphereMouse(double mouseX, double mouseY, SphericalTransformComponent* pSphericalTransform, 
    DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, 
    double r_sphere, double w_sphere, double mu)
{
    const auto& world = pSphericalTransform->GetWorld();
    auto sphericalPosition = pSphericalTransform->GetSphericalPosition();
    auto pos_world = sphericalPosition;
    auto pos = Vector4::Transform(pos_world, view); //pos_view
    auto radius = SphericalEffect::GetRadius();
    double chi = acos(pos.w / radius);
    if (pos.z < 0)
        chi = XM_2PI - chi;


    // РАССЧЕТ НОВОГО ВИДИМОГО РАДИУСА В СООТВЕТСТВИЕ С ТЕМ, ЧТО В ШЕЙДЕРЕ
    // muOriginal - когда была испущена информация
    float startRadius = 0.14f;
    float multiplier = 2.f - startRadius / 2;
    double muOriginal = mu - chi;
    double effectiveRadius = startRadius + multiplier * (1 - cos(muOriginal));
    radius = effectiveRadius; // !!!
    auto w_sphere = radius - 2 * radius * pow(sin(initialObjectRadius / radius / 2), 2);
    auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);

    Vector4 leftReferenceVector(-r_sphere, 0, 0, w_sphere), rightReferenceVector(r_sphere, 0, 0, w_sphere);

    // первая координата - близость к центру (z), вторая x, третья y
    auto sphCoord = GetSphericalFromCartesian(pos.x / radius, pos.y / radius, pos.z / radius, pos.w / radius);
    auto lrvChanged = Vector4::Transform(leftReferenceVector, SphericalRotationZW(sphCoord.x));
    auto rrvChanged = Vector4::Transform(rightReferenceVector, SphericalRotationZW(sphCoord.x));
    auto lrvProjected = Vector4::Transform(lrvChanged, proj);
    auto rrvProjected = Vector4::Transform(rrvChanged, proj);
    if (lrvProjected.w == 0 || rrvProjected.w == 0)
        return -1;
    lrvProjected /= lrvProjected.w;
    rrvProjected /= rrvProjected.w;

    double dist = (rrvProjected.x - lrvProjected.x)/2;
    double distSq = dist * dist;

    auto posProj_4D = Vector4::Transform(pos, proj);
    if (posProj_4D.w == 0)
        return -1;
    auto posProj = Vector3(posProj_4D.x / posProj_4D.w, posProj_4D.y / posProj_4D.w, posProj_4D.z / posProj_4D.w);
   
    auto distFromCursorToCenterSq = pow(posProj.x - mouseX, 2) + pow(posProj.y - mouseY, 2);
    if (distFromCursorToCenterSq > distSq)
        return -1;

    if (pos.z < 0)
        return posProj.z + 1;
    return posProj.z; 
}

    /*
    auto viewChanged = view * SphericalRotationXZ(pos.x > 0 ? -sphCoord.y : sphCoord.y);
    // *SphericalRotationYZ(sphCoord.z);

    auto posChanged = Vector4::Transform(pos_world, viewChanged); //pos_view
    auto sphCoordChanged = GetSphericalFromCartesian(posChanged.x / radius, posChanged.y / radius, posChanged.z / radius, posChanged.w / radius);

    Matrix matrixPosRadiusY(1, 0, 0, 0, 0, w_sphere, 0, r_sphere, 0, 0, 1, 0, 0, -r_sphere, 0, w_sphere);
    Matrix matrixNegRadiusY(1, 0, 0, 0, 0, w_sphere, 0, -r_sphere, 0, 0, 1, 0, 0, r_sphere, 0, w_sphere);
    Matrix matrixPosRadiusX(w_sphere/ radius, 0, 0, r_sphere/ radius,  0, 1, 0, 0, 0, 0, 1, 0, -r_sphere/radius, 0, 0, w_sphere/ radius);
    Matrix matrixNegRadiusX(w_sphere/ radius, 0, 0, -r_sphere/ radius, 0, 1, 0, 0, 0, 0, 1, 0, r_sphere/ radius, 0, 0, w_sphere/ radius);

    Vector4 viewRadiusVectorX1 = Vector4::Transform(pos, matrixPosRadiusX), viewRadiusVectorX2 = Vector4::Transform(pos, matrixNegRadiusX);
    Vector4 projectedRadiusVectorX1 = Vector4::Transform(viewRadiusVectorX1, proj), projectedRadiusVectorX2 = Vector4::Transform(viewRadiusVectorX2, proj);
    if (projectedRadiusVectorX1.w == 0 || projectedRadiusVectorX2.w == 0)
        return -1;
    projectedRadiusVectorX1 /= projectedRadiusVectorX1.w;
    projectedRadiusVectorX2 /= projectedRadiusVectorX2.w;
    auto distSqX = (projectedRadiusVectorX1.x - projectedRadiusVectorX2.x) / 2;
    distSqX = distSqX * distSqX;

    Vector4 viewRadiusVectorY1 = Vector4::Transform(pos, matrixPosRadiusY), viewRadiusVectorY2 = Vector4::Transform(pos, matrixNegRadiusY);
    Vector4 projectedRadiusVectorY1 = Vector4::Transform(viewRadiusVectorY1, proj), projectedRadiusVectorY2 = Vector4::Transform(viewRadiusVectorY2, proj);
    if (projectedRadiusVectorY1.w == 0 || projectedRadiusVectorY2.w == 0)
        return -1;
    projectedRadiusVectorY1 /= projectedRadiusVectorY1.w;
    projectedRadiusVectorY2 /= projectedRadiusVectorY2.w;
    auto distSqY = (projectedRadiusVectorY1.y - projectedRadiusVectorY2.y) / 2;
    distSqY = distSqY * distSqY;

    double distSq = max(distSqX, distSqY);

    */