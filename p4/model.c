#include "model.h"

Book *createBook( char const *id, char const *name )
{
  Book *b = ( Book *)malloc( sizeof( Book ) );

  if( strlen(name) <= MAX_NAME ) {
    strcpy(b->name, name);
  } else {
    printf("error book couldn't be made for some reason: model.c: line 3-14");
  }
  if( strlen(id) <= MAX_ID ) {
    strcpy(b->id, id);
  } else {
    printf("error book couldn't be made for some reason:  model.c: line 3-14");
  }
  b->sold = 0;
  return b;
}

void freeBook( Book *book )
{
  free(book);
}

Salesperson *createSalesperson( char const *id, char const *name )
{
  Salesperson *sp = (Salesperson *)malloc( sizeof( Salesperson ) );

  if( strlen(name) <= MAX_NAME ) {
    strcpy(sp->name, name);
  } else {
    printf("error salesperson couldn't be made for some reason: model.c: line 24");
  }
  if( strlen(id) <= MAX_ID ) {
    strcpy(sp->id, id);
  } else {
    printf("error salesperson couldn't be made for some reason:  model.c: line 24");
  }
  sp->sold = 0;
  sp->head = NULL;
  return sp;
}

void freeSalesperson( Salesperson *salesperson )
{
  while ( salesperson->head ) {
    BookNode *next = salesperson->head->next;
    free( salesperson->head );
    salesperson->head = next;
  }

  free(salesperson);
}

Group *createGroup()
{
  Group *grp = (Group *)malloc( sizeof( Group ) );

  grp->bCount = 0;
  grp->bCap = 4;
  grp->sCap = 4;
  grp->sCount = 0;
  
  grp->bList = ( Book **) malloc(4 * sizeof( Book *));
  grp->sList = ( Salesperson **) malloc(4 * sizeof( Salesperson *));

  return grp;
}

void freeGroup( Group *group )
{
  for ( int i = 0; i < group->bCount; i++) {
    freeBook(group->bList[i]);
  }
  for ( int i = 0; i < group->sCount; i++) {
    freeSalesperson(group->sList[i]);
  }
  free(group->bList);
  free(group->sList);
  free(group);
}

Book *getBook( Group *group, char const *id )
{
  for (int i = 0; i < group->bCount; i++) {
    if ( strcmp(group->bList[i]->id, id) == 0) {
      return group->bList[i];
    }
  }
  return NULL;
}
  

Salesperson *getSalesperson( Group *group, char const *id )
{
  for (int i = 0; i < group->sCount; i++) {
    if ( strcmp(group->sList[i]->id, id) == 0) {
      return group->sList[i];
    }
  }
  return NULL;
}
