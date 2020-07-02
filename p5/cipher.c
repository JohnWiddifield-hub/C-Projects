static char code[256][24] = {};

void loadCipher( char const *filename )
{
  for (int i = 0; i < 256; i++ ) {
    for (int j = 0; j < 24; j++ ) {
      code[i][j] = '\0';
    }
  }
  FILE *fp = fopen(filename, "r");
  if(fp == NULL) {
    perror( filename );
    exit(EXIT_FAILURE);
  }

  int idx = 0;
  int rev = 0;
  while (fscanf(fp, "%s\n", code[idx]) == 1) {
    if (idx >= 256) {
      printf("Invalid code file: %s\n", filename);
    }
    if (strlen(code[idx]) > 24) {
      printf("Invalid code file: %s\n", filename);
    }
    if (idx != 0) {
      rev = idx - 1;
      for (int i = rev; i >= 0; i--) {
        if (strncmp(code[idx], code[i], strlen(code[idx])) == 0) {
          printf("Invalid code file: %s\n", filename);
        }
      }
    }
    idx++;
    
  }
  if (idx != 255 ) {
    printf("Invalid code file: %s\n", filename);
  }
 
}

void freeCipher()
{
  return;
}

char const *getCipher( unsigned char byte )
{
 return code[byte];
}

int lookupCipher( char const *bits )
{
  for (int i = 0; i < 256; i++) {
    if ( strcmp(bits, code[i]) == 0 ) {
      if ( strlen(bits) == strlen(code[i]) ) {
        return i;
      } else {
        return CIPHER_PREFIX;
      }
    }
  }
   return CIPHER_INVALID;
}
