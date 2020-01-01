//
// Created by Ben Koren Kruiger on 26/12/2019.
//

#ifndef ASSI3_OBJECT_H
#define ASSI3_OBJECT_H

#include "Vertex.h"
#include "Face.h"

typedef struct {
    // Array of all Vertexes
    int numberOfVertexes;
    Vertex *vertexes;
    // Array of all Faces
    int  numberOfFaces;
    Face *faces;
} Object;

#endif //ASSI3_OBJECT_H
