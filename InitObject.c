#pragma once

#include "Object.h"
// initializing Faces by getting all Vertexes + calling to a help func getLen for each Face.
void initFaces(Face *faces,FILE *file);
//getting number of Vertexes in each Face for specifying size in memory with malloc.
int getLen(const char *line);
// initializing all Vertexes in the file.
void initVertex(Vertex *vertexes,FILE *file);
// getting the number of Vertexes in the file for specifying place in memory.
int numOfVertexs(FILE *file);
// getting the number of Faces in file for specifying place in memory.
int numOfFaces(FILE *file);
// Creating Object from the given file.
Object *createObject (char *filename) {
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen(filename, "r");
    if (f == NULL){
        printf("Error there is a problem with the file.");
        return NULL;
    }
    int vQuantity = numOfVertexs(f);
    int fQuantity = numOfFaces(f2);
    Object *obj = (Object*)malloc(sizeof(Object));
    obj->numberOfVertexes = vQuantity;
    obj->numberOfFaces = fQuantity;
    obj->faces = (Face*)malloc(fQuantity*sizeof(Face));
    obj->vertexes = (Vertex*)malloc(vQuantity*sizeof(Vertex));
    if(obj->faces == NULL || obj->vertexes == NULL)
        return NULL;
    rewind(f);
    rewind(f2);
    initVertex(obj->vertexes,f);
    initFaces(obj->faces,f2);

    return obj;
}

void initFaces(Face *faces,FILE *file) {
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    int num = 0, i =0 ,indexVer = 0,faceIndex = 0,length = 0, flag = 0,number =0;
    while (!feof(file)) {
        getline(&line, &len, file);
        if(line[0] == 'f' && line[1] == ' '){
            length = getLen(line);
            faces[faceIndex].size = length;
            faces[faceIndex].vertex = (int *)malloc( length*sizeof(int*));
            char *tempNum = (char*)malloc(length* sizeof(char*));
            for (int j = 0; j < strlen(line); ++j) {
                if(line[j] == ' '){
                    flag = 1;
                }else if(line[j]== '/'){
                    flag = 0;
                    i = 0;
                    sscanf(tempNum,"%d",&num);
                }else if(flag == 1){
                    tempNum[i] = line[j];
                    i++;
                }
                if(tempNum[0] != '\0' && flag == 0){
                    faces[faceIndex].vertex[indexVer] = num;
                    indexVer++;
                    tempNum = (char*)malloc(length* sizeof(char*));
                }
            }
//            free(tempNum);
            indexVer=0;
            faceIndex++;
        }
        number++;
    }
    free(line);
}

int getLen(const char *line) {
    char *token = (char *)malloc(4*sizeof(char));
    int flag = 0;int len = 0;int index = 0,numOfSpace = 0;
    for (int i = 0; i < strlen(line); ++i) {
        if(line[i] == ' '){
            if(numOfSpace == 0) {
                len++;
                numOfSpace++;
            }
            flag = 1;
        }else if(line[i]== '/'){
            flag=0;
            numOfSpace =0;
        }else if(flag ==1){
            token[index] = line[i];
            index++;
            numOfSpace =0;
        }
    }
    free(token);
    return len;
}

void initVertex(Vertex *vertexes,FILE *file) {
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    float x,y,z;
    int i = 0;
    while (!feof(file)) {
        getline(&line, &len, file);
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line,"%*[^-0123456789]%f%*[^-0123456789]%f%*[^-0123456789]%f", &x,&y,&z);
            vertexes[i].x = x;
            vertexes[i].y = y;
            vertexes[i].z = z;
            i++;
        }
    }
    free(line);
}
int numOfVertexs(FILE *file){
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    int counter=0;
    while(!feof(file)){
        getline(&line, &len, file);
        if(line[0] =='v' && line[1] == ' ')
            counter++;
    }
    free(line);
    return counter;
}
int numOfFaces(FILE *file){
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    int counter=0;
    while(!feof(file)){
        getline(&line, &len, file);
        if(line[0] =='f' && line[1] == ' ')
            counter++;
    }
    free(line);
    return counter;
}