/**
This is the header file for the model of the cookie program
@file model.h
@author John Widdifield and NCSU staff
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/** Maximum length of a cookie or scout unique id. */
#define MAX_ID 5

/** Maximum length of a cookie or scout name. */
#define MAX_NAME 30

/**maximum length of a command line */
#define MAX_LINE 50

/**number for doubling the capacity */
#define DOUBLE_CAP 2

/** initial capacity for arrays */
#define INITIAL_CAPACITY 4

/** Representation for a cookie. */
typedef struct {
  /** Unique ID for this cookie, containing no whitespace */
  char id[ MAX_ID + 1 ];

  /** Name of this cookie (maybe not unique, and maybe with whitespace). */
  char name[ MAX_NAME + 1 ];

  /** Number of boxes sold. */
  int boxes;

} Cookie;

/** Node for linked list of cookies. */
struct CookieNodeStruct {

  /** Cookie pointer */
  Cookie *cookie;

  /** Number of boxes sold */
  int boxes;

  /** Pointer to the next node. */
  struct CookieNodeStruct *next;
};

// A short type name to use for a node.
typedef struct CookieNodeStruct CookieNode;

/** Representation for a scout in the troop. */
typedef struct {
  /** Unique ID for this scout (containing no whitespace). */
  char id[ MAX_ID + 1 ];

  /** Name for this scout (maybe not unique and maybe whitespace). */
  char name[ MAX_NAME + 1 ];

  /** List of all cookies sold by scout. */
  CookieNode *head;

  /** Total number of boxes sold. */
  int boxes;
  
} Scout;

/** Representation for the whole troop, containing a resizable list of cookies
    and a resizable list of scouts. */
typedef struct {

  /** List of all cookies. */
  Cookie **cList;

  /** Capacity of the cList array. */
  int cCap;

  /** Number of cookies. */
  int cCount;
  
  /** List of all the scouts. */
  Scout **sList;
  
  /** Capacity of the current sList array. */
  int sCap;

  /** Number of scouts. */
  int sCount;
} Troop;

/*
Dynamically allocates a Cookie
@param id id for the cookie
@param name name of the cookie
@return the pointer to the new cookie
*/
Cookie *createCookie( char const *id, char const *name );

/*
Frees the memory for the cookie.
@param cookie  cookie to free
*/
void freeCookie( Cookie *cookie );

/*
Dynamically allocates an instance of Scout
@param id id for the scout
@param name name for the scout
*/
Scout *createScout( char const *id, char const *name );
/*
Frees the memory for the scout
@param scout scout to free
*/
void freeScout( Scout *scout );

/*
This dynamically allocates an instance of Troop
@return a new troop
*/
Troop *createTroop();

/*
This will free the memory used for a given troop
@param troop troop to free
*/
void freeTroop( Troop *troop );

/*
This will get a cookie
@param troop troop which contains the cookie
@param id id of the cookie you want
@return cookie with the matc hing ID or null if it does not exist
*/
Cookie *getCookie ( Troop *troop, char const *id );

/*
This will get a scout
@param troop troop which contains the scout
@param id id of the scout you wish to retrieve
@return the scout with the matching ID
*/
Scout *getScout( Troop *troop, char const *id );
