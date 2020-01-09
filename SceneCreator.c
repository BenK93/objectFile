#pragma once
#include <stdarg.h>
#include "InitObject.c"
#include "Scene.h"

// Creating an One way list and returning Scene.
Scene *createScene(char *fileName, ...){
    va_list files;
    va_start(files,fileName);
    Scene *scene = (Scene *)malloc(sizeof(Scene));
    if(scene == NULL) {
        printf("No space in memory");
        return NULL;
    }
    char *currentFile = fileName;
    scene->head = (Node*)malloc(sizeof(Node));
    Node *pointer = (*scene).head;
    while(currentFile != NULL){
        Object *currentObj = createObject(currentFile);
        pointer->object = currentObj;
        currentFile = va_arg(files,char*);
        if(currentFile == NULL){
            pointer->next = NULL;
            break;
        }
        pointer->next = (Node *)malloc(sizeof(Node));
        pointer = pointer->next;
    }
    va_end(files);
    return scene;
}
