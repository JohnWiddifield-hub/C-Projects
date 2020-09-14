/*
This program models a troop of girl scouts progress with selling cookies
@author John Widdifield
@file model.c
*/
#include "model.h"


/*
Dynamically allocates a Cookie
@param id id for the cookie
@param name name of the cookie
@return the pointer to the new cookie
*/
Cookie *createCookie( char const *id, char const *name )
{
  Cookie *newCookie = ( Cookie *)malloc( sizeof( Cookie ) );
  strncpy(newCookie->id, id, sizeof( newCookie->id ) - 1 );
  newCookie->id[ sizeof( newCookie->id ) - 1 ] = '\0';
  strncpy(newCookie->name, name, sizeof( newCookie->name ) - 1 );
  newCookie->name[ sizeof( newCookie->name ) - 1 ] = '\0';
  newCookie->boxes = 0;
  return newCookie;
}

/*
Frees the memory for the cookie.
@param cookie  cookie to free
*/
void freeCookie( Cookie *cookie )
{
  free(cookie);
}

/*
Dynamically allocates an instance of Scout
@param id id for the scout
@param name name for the scout
*/
Scout *createScout( char const *id, char const *name )
{
  Scout *newScout = ( Scout *)malloc( sizeof( Scout ) );
  strncpy(newScout->id, id, sizeof( newScout->id ) - 1 );
  newScout->id[ sizeof( newScout->id ) - 1 ] = '\0';
  strncpy(newScout->name, name, sizeof( newScout->name ) - 1 );
  newScout->name[ sizeof( newScout->name ) - 1 ] = '\0';
  newScout->boxes = 0;
  newScout->head = NULL;
  return newScout;
}

/*
Frees the memory for the scout
@param scout scout to free
*/
void freeScout( Scout *scout )
{
  while ( scout->head ) {
    CookieNode *next = scout->head->next;
    free( scout->head );
    scout->head = next;
  }

  free(scout);
}

/*
This dynamically allocates an instance of Troop
@return a new troop
*/
Troop *createTroop()
{
  Troop *troop = ( Troop * ) malloc(sizeof( Troop));
  troop->cList = (Cookie **) malloc(INITIAL_CAPACITY * sizeof(Cookie * ));
  troop->cCap = INITIAL_CAPACITY;
  troop->cCount = 0;
  troop->sList = (Scout **) malloc(INITIAL_CAPACITY * sizeof(Scout * ));
  troop->sCap = INITIAL_CAPACITY;
  troop->sCount = 0;
  return troop;
}

/*
This will free the memory used for a given troop
@param troop troop to free
*/
void freeTroop( Troop *troop )
{
  for ( int i = 0; i < troop->cCount; i++ ) {
    freeCookie(troop->cList[i]);
  }
  
  for ( int i = 0; i < troop->sCount; i++ ) {
    freeScout(troop->sList[i]);
  }
  free(troop);
}

/*
This will get a cookie
@param troop troop which contains the cookie
@param id id of the cookie you want
@return cookie with the matching ID or null if it does not exist
*/
Cookie *getCookie ( Troop *troop, char const *id )
{
  for ( int i = 0; i < troop->cCount; i++ ) {

    if ( strncmp(troop->cList[i]->id, id, sizeof(id) - strlen(id) - 1) == 0) {
      return troop->cList[i];
    }
    
  }
  return NULL;
}

/*
This will get a scout
@param troop troop which contains the scout
@param id id of the scout you wish to retrieve
@return the scout with the matching ID
*/
Scout *getScout( Troop *troop, char const *id )
{
  for ( int i = 0; i < troop->sCount; i++ ) {

    if ( strncmp(troop->sList[i]->id, id, sizeof(id) - strlen(id) - 1) == 0) {
      return troop->sList[i];
    }
    
  }
  return NULL;
}
