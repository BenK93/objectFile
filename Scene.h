//
// Created by Ben Koren Kruiger on 26/12/2019.
//

#ifndef ASSI3_SCENE_H
#define ASSI3_SCENE_H

#include "Object.h"

typedef struct Node{
    Object *object;
    struct Node *next;
}Node;
typedef struct {
    // This structure contains a Single Direction Linked List of all objects in the Scene
    Node *head;
} Scene;

enum FileType { TextFormat, BinaryFormat };

#endif //ASSI3_SCENE_H
