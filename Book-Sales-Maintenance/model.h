/**
This contains all of the structures necessary for the tracker program as well as
functionality for allocating and freeing the memory used for the implemented data structures
@file model.h
@author John Widdifield (jfwiddif)
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** Initial capacity for resizeable arrays */
#define INIT_CAP 4

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

/**
This will dynamically create a book struct containing the name and id given
@param id book id
@param name name of the book
@return Book pointer to the created Book struct
*/
Book *createBook( char const *id, char const *name );

/**
This will dynamically create a salesperson struct containinng the name and id given
@param id salesperson id
@param name name of the saleperson
@return Salesperson pointer to the created Salesperson struct
*/
Salesperson *createSalesperson( char const *id, char const *name );

/**
This will dynamically create a group structure which contains a lists of salespeople and books
@return Group pointer to the created group structure
*/
Group *createGroup();

/**
This will free all memory associated with the group including the salespeople books and linked
lists which contain the salespeoples books
@param group group which you wish to free the memory of
*/
void freeGroup( Group *group );

/**
This will retrieve a book from the group which contains it
@param group group which contains a specified book
@param id id of the book you wish to retrieve
@return Book the book which matches the given id or null if group doesn't contain it
*/
Book *getBook( Group *group, char const *id );

/**
This will retrieve a salesperson from the group which contains it
@param group group which contains a specified salesperson
@param id id of the salesperson you wish to retrieve
@return the Salesperson which matches the given id or null if group doesn't contain the person
*/
Salesperson *getSalesperson( Group *group, char const *id );
