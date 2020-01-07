#pragma once

void convertToXYZ(char *line, FILE *pFile);

void transformObject(char *originalObjectFileName, char *deformedObjectFileName);

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
