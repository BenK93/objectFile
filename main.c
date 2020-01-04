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

Scene *createScene(char *fileName, ...);

void initVertex(Vertex *vertexes,FILE *file);

void initFaces(Face *faces, FILE *file);

int getLen(char *line);

int main() {
    transformObject("Donald.obj","DeformedDonald.obj");
    Object *obj = createObject("Donald.obj");
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
    rewind(f);
    rewind(f2);
    initVertex(obj->vertexes,f);
    initFaces(obj->faces,f2);

    return obj;
}

void initFaces(Face *faces,FILE *file) {
    char *line =(char *)malloc(sizeof(char));
    size_t len =0;
    int num = 0;
    int i =0;
    int indexVer = 0;
    int faceindex = 0;
    int length = 0;
    int flag = 0;
    while (!feof(file)) {
        getline(&line, &len, file);
        if(line[0] == 'f' && line[1] == ' '){
            length = getLen(line);
            faces[faceindex].vertex = (int *)malloc( length*sizeof(int));
            char *tempNum = (char*)malloc(length* sizeof(char));
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
                    faces[faceindex].vertex[indexVer] = num;
                    indexVer++;
                    tempNum[0] = '\0';
                }
            }
            free(tempNum);
            faces->size = length;
            indexVer=0;
            faceindex++;
        }
    }
    free(line);
}

int getLen(char *line) {
    char *token = (char *)malloc(4*sizeof(char));
    int flag = 0;int len = 0;int index = 0;
    for (int i = 0; i < 8; ++i) {
        if(line[i] == ' '){
            flag = 1;
        }else if(line[i]== '/'){
            len = strlen(token);
            break;
        }else if(flag ==1){
            token[index] = line[i];
            index++;
        }
    }
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
