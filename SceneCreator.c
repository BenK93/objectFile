#pragma once
#include <stdarg.h>
#include "InitObject.c"
#include "List.c"
#include "List.h"

char* firstFile(const char* fileName);
Scene *createScene(char *fileName, ...){
    va_list files;
    va_start(files,fileName);
    Scene *scene = (Scene *)malloc(sizeof(Scene));
    if(scene == NULL) {
        printf("No space in memory");
        return NULL;
    }
    char *currentFile = firstFile(fileName);
    NODE *pointer = &scene->list->head;
    while(currentFile != NULL){

        Object *currentObj = createObject(currentFile);
        pointer = L_insert(pointer,currentObj);
        currentFile = va_arg(files,char*);
    }
    va_end(files);
    scene->list->head = *pointer;
    return scene;
}

char* firstFile(const char* fileName){
    char *name = (char*)malloc(sizeof(char));
    int i =0;
    while(fileName[i] != '\0'){
        name[i] = fileName[i];
        i++;
    }
    return name;
}