#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Vertex.h"
#include "Scene.h"
#include "Face.h"
#include "Object.h"

void transformObject(char *originalObjectFileName, char *deformedObjectFileName);

void convertToXYZ(char *line, FILE *pFile);

Object *createObject (char *filename);

int numOfVertexs(FILE *file);

int numOfFaces(FILE *file);

void initVertex(Vertex *vertexes, int quantity,FILE *file);

void initFaces(Face *faces, int quantity, FILE *file);

int main() {
    transformObject("Donald.obj","DeformedDonald.obj");
//    Object *obj = createObject("Donald.obj");
    return 0;
}

void transformObject(char *originalObjectFileName, char *deformedObjectFileName){
    FILE *fOriginal = fopen(originalObjectFileName, "r");
    FILE *fDeformed = fopen(deformedObjectFileName, "w");
    if(fDeformed == NULL || fOriginal == NULL){
        printf("One of the files is not okay, ERROR.");
    }
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    while(!feof(fOriginal)){
        getline(&line, &len, fOriginal);
        if(line[0] =='v'){
            convertToXYZ(line, fDeformed);
        }else {
            fprintf(fDeformed, "%s", line);
        }
    }
    fclose(fOriginal);
    fclose(fDeformed);
    free(line);
}

void convertToXYZ(char *line, FILE *pFile) {
    float x,y,z;
    sscanf(line,"%*[^-0123456789]%f%*[^-0123456789]%f%*[^-0123456789]%f", &x,&y,&z);
    if(line[1] == ' '){
        fprintf(pFile, "v  %.6f %.6f %.6f\n",x*0.3, y,z);
    }else {
        fprintf(pFile,"%s",line);
    }
}
Object *createObject (char *filename){
    FILE *f = fopen(filename,"r");
    if(f ==NULL)
        printf("Error thers is problem with the file.");
    int vQuantity = numOfVertexs(f);
    int fQuantity = numOfFaces(f);
    Object *obj = (Object*)malloc(sizeof(Object));
    obj->numberOfVertexes = vQuantity;
    obj->numberOfFaces = fQuantity;
    obj->faces = (Face*)malloc(sizeof(Face));
    obj->vertexes = (Vertex*)malloc(sizeof(Vertex));
    initVertex(obj->vertexes,vQuantity,f);
    initFaces(obj->faces,fQuantity,f);
    return obj;
}

void initFaces(Face *faces, int quantity, FILE *file) {
    faces = malloc(quantity*sizeof(Vertex));
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    float x,y,z;
    for (int i = 0; i < quantity; ++i) {
        getline(&line, &len, file);
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line,"%*[^-0123456789]%f%*[^-0123456789]%f%*[^-0123456789]%f", &x,&y,&z);
            faces[i].x = x;
            faces[i].y = y;
            faces[i].z = z;
        }
    }
    free(line);
}

void initVertex(Vertex *vertexes, int quantity,FILE *file) {
    vertexes = malloc(quantity*sizeof(Vertex));
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    float x,y,z;
    for (int i = 0; i < quantity; ++i) {
        getline(&line, &len, file);
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line,"%*[^-0123456789]%f%*[^-0123456789]%f%*[^-0123456789]%f", &x,&y,&z);
            vertexes[i].x = x;
            vertexes[i].y = y;
            vertexes[i].z = z;
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
