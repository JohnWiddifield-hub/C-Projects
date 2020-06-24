/**
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Maximum length of a book or salesperson unique id. */
#define MAX_ID 5

/** Maximum length of a book or salesperson name. */
#define MAX_NAME 30

/** Representation for a book. */
typedef struct {
  /** Unique ID for this book, containing no whitespace */
  char id[ MAX_ID + 1 ];

  /** Name of this book (maybe not unique, and maybe with whitespace). */
  char name[ MAX_NAME + 1 ];

  /** Number of books sold. */
  int sold;
  
} Book;

/** Node for linked list of books. */
struct BookNodeStruct {
  
  /** Book pointer */
  Book *book;

  /** Number of books sold */
  int sold;

  /** Pointer to the next node. */
  struct BookNodeStruct *next;
};

// A short type name to use for a node.
typedef struct BookNodeStruct BookNode;

/** Representation for a salesperson in the group. */
typedef struct {
  /** Unique ID for this salesperson (containing no whitespace). */
  char id[ MAX_ID + 1 ];

  /** Name for this salesperson (maybe not unique and maybe whitespace). */
  char name[ MAX_NAME + 1 ];

  /** List of all books sold by salesperson. */
  BookNode *head;

  /** Total number of books sold. */
  int sold;
  
} Salesperson;

/** Representation for the whole group, containing a resizable list of books
    and a resizable list of salespersons. */
typedef struct {

  /** List of all books. */
  Book **bList;

  /** Capacity of the bList array. */
  int bCap;

  /** Number of books. */
  int bCount;
  
  /** List of all the salespersons. */
  Salesperson **sList;
  
  /** Capacity of the current sList array. */
  int sCap;

  /** Number of salespersons. */
  int sCount;
} Group;

Book *createBook( char const *id, char const *name );

void freeBook( Book *book );

Salesperson *createSalesperson( char const *id, char const *name );

void freeSalesperson( Salesperson *salesperson );

Group *createGroup();

void freeGroup( Group *group );

Book *getBook( Group *group, char const *id );

Salesperson *getSalesperson( Group *group, char const *id );

