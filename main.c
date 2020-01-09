#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Scene.h"
#include "Object.h"
#include "transform.c"
#include "InitObject.c"
#include "SceneCreator.c"


void perform(Scene *scene, void(*function)(Object *, void *), char *type , char *sentence);

void printFaces(Object *obj, void *numberOfTriangularFaces);

void printVertexes(Object *obj, void *numberOfVertexes);

void getTotalArea (Object *obj, void *totalAreaOfTriangularFaces);

void saveFormat(Scene *scene, FILE *f ,enum FileType type);

void saveScene(Scene *scene, char *fileName, enum FileType type);

Scene *loadScene(char *fileName, enum FileType type);


void freeScene(Scene *scene);

int main() {
    Scene *scene;
    Scene *scene1, *scene2;

    // Create a Scene of Objects received
    // from files GoingMerry.obj, Donald.obj, Pony_cartoon.obj
    scene = createScene("GoingMerry.obj", "Donald.obj","Pony_cartoon.obj", NULL);
    // Print out all Vertexes
    perform(scene, printVertexes, "INT" ,"The number of vertexes of all objects is");

    // Count the number of all Triangular faces of all objects in Scene
    perform(scene, printFaces, "INT", "The number of Triangular faces of all objects is");

    // Count the total area of all Triangular faces of all objects in Scene
    perform(scene, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");

    // Save the world to file in Text and in Binary formats
    saveScene(scene, "FirstScene.dat", TextFormat);
    saveScene(scene, "SecondScene.dat", BinaryFormat);

    // Retrieve the saved data
    scene1 = loadScene("FirstScene.dat", TextFormat);
    scene2 = loadScene("SecondScene.dat", BinaryFormat);

//    // Check Retrieve the saved data of text format
//    perform(scene1, printVertexes, "INT" ,"The number of vertexes of all objects is");
//    perform(scene1, printFaces,"INT", "The number of Triangular faces of all objects is");
//    perform(scene1, getTotalArea,"DOUBLE", "The total area of Triangular faces of all objects is");
//    // Check Retrieve the saved data of binary format
//    perform(scene2, printVertexes,"INT" ,"The number of vertexes of all objects is");
//    perform(scene2, printFaces,"INT", "The number of Triangular faces of all objects is");
//    perform(scene2, getTotalArea,"DOUBLE", "The total area of Triangular faces of all objects is");
//
////    // Make transformation based on the original object defined in file Donald.obj
//    transformObject("Donald.obj", "StrangeDonald.obj");


//     Free all memory allocated for the Scene
//    freeScene(scene);
//    freeScene(scene1);
//    freeScene(scene2);

}


void perform(Scene *scene, void(*function)(Object *, void *), char *type , char *sentence) {
    struct Node *ptr = scene->head;
    if (strcmp(type, "INT") == 0) {
        int num = 0;
        while (ptr != NULL) {
            function(ptr->object, &num);
            ptr = ptr->next;
        }
        printf("%s: %d\n", sentence, num);
    } else if (strcmp(type, "DOUBLE") == 0) {
        double num = 0;
        while (ptr != NULL) {
            function(ptr->object, &num);
            ptr = ptr->next;
        }
        printf("%s: %f\n", sentence, num);
    }
}
void printVertexes(Object *obj, void *numberOfVertexes){
    *((int*)numberOfVertexes) += obj->numberOfVertexes;
}
void printFaces(Object *obj, void *numberOfTriangularFaces){
    int counter = 0, size = 0;
    for (int i = 0; i < obj->numberOfFaces; ++i) {
        size = obj->faces[i].size;
        if(size == 3){
            counter++;
        }
    }
    *((int*)numberOfTriangularFaces) += counter;
}
void getTotalArea (Object *obj, void *totalAreaOfTriangularFaces){
    double totoalArea = 0;int number =0;
    for (int i = 0; i < obj->numberOfFaces; ++i) {
        if(obj->faces[i].size == 3){
        double currentArea = 0,s=0;
        int index1 = obj->faces[i].vertex[0]-1;
        int index2 = obj->faces[i].vertex[1]-1;
        int index3 = obj->faces[i].vertex[2]-1;
        double rib1 = sqrt(pow(obj->vertexes[index1].x - obj->vertexes[index2].x,2)+pow(obj->vertexes[index1].y - obj->vertexes[index2].y,2)
                +pow(obj->vertexes[index1].z - obj->vertexes[index2].z,2));
        double rib2 = sqrt(pow(obj->vertexes[index1].x - obj->vertexes[index3].x,2)+pow(obj->vertexes[index1].y - obj->vertexes[index3].y,2)
                +pow(obj->vertexes[index1].z - obj->vertexes[index3].z,2));
        double rib3 = sqrt(pow(obj->vertexes[index2].x - obj->vertexes[index3].x,2)+pow(obj->vertexes[index2].y - obj->vertexes[index3].y,2)
                +pow(obj->vertexes[index2].z - obj->vertexes[index3].z,2));
        s = (rib1+rib2+rib3)/2;
        currentArea = sqrt(s*(s-rib1)*(s-rib2)*(s-rib3));
        totoalArea += currentArea;
        if(totoalArea != NAN)
            number++;
        }
    }
    *((double*)totalAreaOfTriangularFaces) += totoalArea;
}
void saveScene(Scene *scene, char *fileName, enum FileType type){
    FILE *f;
    if(type == TextFormat){
        f = fopen(fileName,"w");
        if(f == NULL)
            return;
        saveFormat(scene,f,type);
    }else if(type == BinaryFormat){
        f = fopen(fileName,"wb");
        if(f == NULL)
            return;
        saveFormat(scene,f,type);
    }else {
        return;
    }
    fclose(f);
}
void saveFormat(Scene *scene, FILE *file, enum FileType type) {
    Node *pointer = scene->head;
    while (pointer != NULL) {
        if (type == TextFormat){
            for (int i = 0; i < pointer->object->numberOfVertexes; ++i) {
                fprintf(file, "v %f %f %f\n", pointer->object->vertexes[i].x, pointer->object->vertexes[i].y,
                        pointer->object->vertexes[i].z);
            }
            for (int i = 0; i < pointer->object->numberOfFaces; ++i) {
                char *string = (char *) malloc(sizeof(char *));
                string[0] = 'f';
                for (int j = 0; j < pointer->object->faces->size; ++j) {
                    char *num = (char *) malloc(sizeof(char *));
                    strncat(string, " ", 1);
                    sprintf(num, "%d", pointer->object->faces->vertex[j]);
                    double length = floor(log10(abs(pointer->object->faces->vertex[j]))) + 1;
                    strncat(string, num, length);
                }
                fprintf(file, "%s\n", string);
            }
        }else if (type == BinaryFormat) {
            for (int i = 0; i < pointer->object->numberOfVertexes; ++i){
                fwrite("v ",sizeof(char),2,file);
                fwrite(&pointer->object->vertexes[i].x, sizeof(float),1,file);
                fwrite(" ",sizeof(char),1,file);
                fwrite(&pointer->object->vertexes[i].y, sizeof(float),1,file);
                fwrite(" ",sizeof(char),1,file);
                fwrite(&pointer->object->vertexes[i].z, sizeof(float),1,file);
                fwrite("\n",sizeof(char),2,file);
            }
            for (int i = 0; i < pointer->object->numberOfFaces; ++i) {
                char *string = (char *) malloc(sizeof(char *));
                string[0] = 'f';
                for (int j = 0; j < pointer->object->faces->size; ++j) {
                    char *num = (char *) malloc(sizeof(char *));
                    strncat(string, " ", 1);
                    sprintf(num, "%d", pointer->object->faces->vertex[j]);
                    double length = floor(log10(abs(pointer->object->faces->vertex[j]))) + 1;
                    strncat(string, num, length);
                }
                int len = strlen(string);
                fwrite(&string, sizeof(char),len, file);
            }
        }
        pointer = pointer->next;
    }
}
Scene *loadScene(char *fileName, enum FileType type){
    FILE *f;
    if(type == TextFormat){
        f = fopen(fileName,"r");
        if(f == NULL)
            return NULL;
        char *line =(char *)malloc(sizeof(char));size_t len =0;int vFlag =1 ,fFlag=1;
        while(!feof(f)){
            getline(&line, &len, f);
            if(vFlag){
                if(line[0] == 'f') {
                    vFlag = 0;
                    fFlag =1;
                }
            }else if (fFlag){
                if(line[0] == 'v') {
                    fFlag = 0;
                }
            }else if(){

            }
        }
    }else if(type == BinaryFormat){
        f = fopen(fileName,"rb");
        if(f == NULL)
            return NULL;

    }else {
        return NULL;
    }
    fclose(f);
}