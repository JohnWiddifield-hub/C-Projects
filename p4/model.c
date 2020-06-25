/**
This file models a group of salespeople and their book sales it also simplifies the model's
freeing of memory
@file model.c
@author John Widdifield (jfwiddif)
*/
#include "model.h"

/**
This will free the memory of a given book
@param book book you wish to free memory of
*/
static void freeBook( Book *book )
{
  free(book);
}

/**
This will free the memory and associated memory of a given salesperson
@param salesperson the salesperson you wish to free the memory of
*/
static void freeSalesperson( Salesperson *salesperson )
{
  while ( salesperson->head ) {
    BookNode *next = salesperson->head->next;
    free( salesperson->head );
    salesperson->head = next;
  }

  free(salesperson);
}

Book *createBook( char const *id, char const *name )
{
  Book *b = ( Book *)malloc( sizeof( Book ) );

  if (strlen(name) <= MAX_NAME ) {
    strcpy(b->name, name);
  }
  if ( strlen(id) <= MAX_ID ) {
    strcpy(b->id, id);
  }
  b->sold = 0;
  return b;
}

Salesperson *createSalesperson( char const *id, char const *name )
{
  Salesperson *sp = (Salesperson *)malloc( sizeof( Salesperson ) );

  if ( strlen(name) <= MAX_NAME ) {
    strcpy(sp->name, name);
  }
  if ( strlen(id) <= MAX_ID ) {
    strcpy(sp->id, id);
  }
  sp->sold = 0;
  sp->head = NULL;
  return sp;
}

Group *createGroup()
{
  Group *grp = (Group *)malloc( sizeof( Group ) );

  grp->bCount = 0;
  grp->bCap = INIT_CAP;
  grp->sCap = INIT_CAP;
  grp->sCount = 0;

  grp->bList = ( Book **) malloc(INIT_CAP * sizeof( Book *));
  grp->sList = ( Salesperson **) malloc(INIT_CAP * sizeof( Salesperson *));

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
