#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAXWORDS 5000
#define MAXWORDLEN 20

void readWords(FILE *wordListFile, char storage[][21], char fName[]);

bool checkValidity(char aWord[]);

bool checkDuplicate (char aWord[], char storage[][21], int idx);
