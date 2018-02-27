//
// Created by bence on 2018.02.27..
//

#ifndef GRAFIKA_AABB_H
#define GRAFIKA_AABB_H

typedef struct {
    float x;
    float y;
}Vector2f;

typedef struct{
    Vector2f distance;
    int isIntersecting; //0 not , 1 intersects
} Collision;

typedef struct {
    Vector2f center;
    Vector2f half_extent;
}AABBbox;


Collision getCollision(AABBbox box1, AABBbox box2);
AABBbox correctPosition(AABBbox box1, AABBbox box2, Collision collision);
Vector2f vectorSubtract(Vector2f vector1, Vector2f vector2);
Vector2f vectorAdd(Vector2f vector1, Vector2f vector2);

#endif //GRAFIKA_AABB_H
