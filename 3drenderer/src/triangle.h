#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"

typedef struct {
	int a;
	int b;
	int c; 
} face_t; //stores the vertex index


typedef struct {
	vec2_t points[3];
}triangle_t; //stores the actual vector position based off face_t

#endif