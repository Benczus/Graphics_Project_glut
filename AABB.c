//
// Created by bence on 2018.02.27..
//

#include "AABB.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

Collision getCollision(AABBbox box1, AABBbox box2){
    Vector2f distance= vectorSubtract(box2.center, box1.center);
    distance.x= (float) fabs(distance.x);
    distance.y= (float) fabs(distance.y);
    distance=vectorSubtract(distance, vectorAdd(box1.half_extent, box2.half_extent));
    Collision collision;
    collision.distance=distance;
    if (distance.x<0 && distance.y<0){
        collision.isIntersecting=1;
    }else
        collision.isIntersecting=0;
    return collision;
}


AABBbox correctPosition(AABBbox box1, AABBbox box2, Collision collision){
    Vector2f correction= vectorSubtract(box2.center, box1.center);
    if (collision.distance.x > collision.distance.y){
        if (correction.x>0){
            box1.center.x+=collision.distance.x;
        }
        else
            box1.center.x-=collision.distance.x;

    } else{
        if (correction.y>0){
            box1.center.y+=collision.distance.y;
        } else{
            box1.center.y-=collision.distance.y;
        }

        }
    return box1;
}


Vector2f vectorSubtract(Vector2f vector1, Vector2f vector2){
    Vector2f destVector;
    destVector.x=vector1.x-vector2.x;
    destVector.y=vector1.y-vector2.y;
    return destVector;
}
Vector2f vectorAdd(Vector2f vector1, Vector2f vector2){
    Vector2f destVector;
    destVector.x=vector1.x+vector2.x;
    destVector.y=vector1.y+vector2.y;
    return destVector;
}

