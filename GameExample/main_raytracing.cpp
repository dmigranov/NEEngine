#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//todo: исправить для эллиптического случая
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

double RayTraceSphereMouse(double mouseX, double mouseY, SphericalTransformComponent* pSphericalTransform, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_sphere, double w_sphere)
{
    const auto& world = pSphericalTransform->GetWorld();
    auto sphericalPosition = pSphericalTransform->GetSphericalPosition();
    auto pos_world = sphericalPosition;
    auto pos = Vector4::Transform(pos_world, view); //pos_view

    //if (pos.z < 0)  //todo: учесть расстоние
    //    return -1;

    auto radius = SphericalEffect::GetRadius();

    //Matrix matrixPosRadius(1, 0, 0, 0, 0, w_sphere, 0, r_sphere, 0, 0, 1, 0, 0, -r_sphere, 0, w_sphere);
    //Matrix matrixNegRadius(1, 0, 0, 0, 0, w_sphere, 0, -r_sphere, 0, 0, 1, 0, 0, r_sphere, 0, w_sphere);
    Matrix matrixPosRadius(w_sphere/ radius, 0, 0, r_sphere/ radius,  0, 1, 0, 0, 0, 0, 1, 0, -r_sphere/radius, 0, 0, w_sphere/ radius);
    Matrix matrixNegRadius(w_sphere/ radius, 0, 0, -r_sphere/ radius, 0, 1, 0, 0, 0, 0, 1, 0, r_sphere/ radius, 0, 0, w_sphere/ radius);


    /* //это плохо: при повороте на 90 градусов полюса и камера - три точки на прямой, и рассояние между иксами маленькое
    Vector4 radiusVector1(r_sphere, 0, 0, w_sphere);
    Vector4 radiusVector2(-r_sphere, 0, 0, w_sphere);
    Vector4 viewRadiusVector1 = Vector4::Transform(Vector4::Transform(radiusVector1, world), view);
    Vector4 viewRadiusVector2 = Vector4::Transform(Vector4::Transform(radiusVector2, world), view);
    Vector4 projectedRadiusVector1 = Vector4::Transform(viewRadiusVector1, proj);
    Vector4 projectedRadiusVector2 = Vector4::Transform(viewRadiusVector2, proj);
    */

    Vector4 viewRadiusVector1 = Vector4::Transform(pos, matrixPosRadius);
    Vector4 viewRadiusVector2 = Vector4::Transform(pos, matrixNegRadius);
    Vector4 projectedRadiusVector1 = Vector4::Transform(viewRadiusVector1, proj);
    Vector4 projectedRadiusVector2 = Vector4::Transform(viewRadiusVector2, proj);

    if (projectedRadiusVector1.w == 0 || projectedRadiusVector2.w == 0)
        return -1;

    //todo: во-первых, надо инвертировать y!
    projectedRadiusVector1 /= projectedRadiusVector1.w;
    projectedRadiusVector2 /= projectedRadiusVector2.w;
    //std::cout << projectedRadiusVector1.x << " " << projectedRadiusVector1.y << " " << projectedRadiusVector1.z << std::endl;
    //std::cout << projectedRadiusVector2.x << " " << projectedRadiusVector2.y << " " << projectedRadiusVector2.z << std::endl;
    //std::cout << mouseX << " " << mouseY << std::endl << std::endl;

    //auto distSq = pow(projectedRadiusVector1.x - projectedRadiusVector2.x, 2) + pow(projectedRadiusVector1.y - projectedRadiusVector2.y, 2) + pow(projectedRadiusVector1.z - projectedRadiusVector2.z, 2);
    //distSq /= 4;
    auto distSq = (projectedRadiusVector1.x - projectedRadiusVector2.x) / 2;
    distSq = distSq * distSq;


    auto posProj_4D = Vector4::Transform(pos, proj);
    if (posProj_4D.w == 0)
        return -1;
    auto posProj = Vector3(posProj_4D.x / posProj_4D.w, posProj_4D.y / posProj_4D.w, posProj_4D.z / posProj_4D.w);
   
    double distance_sq = pow(posProj.x - projectedRadiusVector1.x, 2) + pow(posProj.y - projectedRadiusVector1.y, 2) + pow(posProj.z - projectedRadiusVector1.z, 2);

    auto distFromCursorToCenterSq = pow(posProj.x - mouseX, 2) + pow(posProj.y - mouseY, 2);
    //std::cout << distFromCursorToCenterSq << std::endl;
    if (distFromCursorToCenterSq > distSq)
        return -1;

    return posProj.z; 
}