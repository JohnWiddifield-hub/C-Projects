/**
This is used to process commands input by the user to modify the group
model such as adding sales or books
@file command.c
@author John Widdifield (jfwiddif)
*/
#include "command.h"

/**
This function will compare two book pointers and is to be used as a comparison function
for qsort for alphabetical order / lexicographical
@param aptr the first book to compare
@param bptr the second book to compare
@return a negative number if aptr should be before bptr a positive number if vice versa
        and 0 if they are considered equal
*/
static int bookComp(const void *aptr, const void *bptr)
{
  Book const *a = *(Book **)aptr;
  Book const *b = *(Book **)bptr;

  if (strcmp( a->name, b->name ) != 0) {
    return strcmp( a->name, b->name );
  } else {
    return strcmp( a->id, b->id );
  }
}

/**
This function will insert a book node into a linked list of BookNodes in sorted order
alphabetically
@param head this is the head of the linked list
@param nBook this is the book you wish to add
@param numSold This is the number of nBooks which were sold
@return the new head for the linked list with the added BookNode
*/
static BookNode *sortInsert( BookNode *head, Book *nBook, int numSold)
{
  for (BookNode *n = head; n; n = n->next) {
    if (strcmp(n->book->id, nBook->id) == 0) {
      n->sold += numSold;
      return head;
    }
  }
  BookNode *new = (BookNode *)malloc( sizeof( BookNode ) );
  new->sold = numSold;
  new->book = nBook;
  if (head == NULL) {
    new->next = NULL;
    return new;
  }
  if (head != NULL && strcmp(nBook->name, head->book->name) < 0) {
    new->next = head;
    return new;
  }

  for (BookNode *n = head; n; n = n->next) {
    if (n->next != NULL && strcmp(nBook->name, n->next->book->name) < 0) {
      new->next = n->next;
      n->next = new;
      return head;
    } else if (n->next == NULL) {
      new->next = NULL;
      n->next = new;
      return head;
    }
  }

  return head;
}

/**
This is the comparison function for salespeople to be used in conjunction with qsort
sorting people by their names alphabetically and by id if they have the same name
@param aptr this is the first pointer to a salesperson to compare
@param bptr this is the second pointer to a salesperson to compare
@return -1 if b belongs before a 1 vice versa and 0 if they are the same
*/
static int spComp(const void *aptr, const void *bptr)
{
  Salesperson const *a = *(Salesperson **)aptr;
  Salesperson const *b = *(Salesperson **)bptr;

  if (a->sold > b->sold ) {
    return -1;
  } else if ( a->sold < b->sold ) {
    return 1;
  } else return strcmp(a->id, b->id);
}

bool processCommand( Group *group )
{
  static int comNum = 1;
  char com[MAX_NAME + 1] = "";
  printf("%d> ", comNum);
  scanf("%s", com);
  comNum++;
 // printf("\n");
  //book command
  if (strcmp(com, "book") == 0) {
    char id[MAX_NAME];
    scanf("%s", id);
    //check if id is the correct length and if it doesn't already exists in the list
    if (strlen(id) <= MAX_ID && getBook(group, id) == NULL && strlen(id) > 0) {
      char name[CHAR_MAX];
      scanf(" %[A-Za-z\' ]s", name);
      if (strlen(name) <= MAX_NAME && strlen(name) > 0) {
        //passes all tests create book and add it to group
        if (group->bCount < group->bCap) {
          group->bList[group->bCount] = createBook(id, name);
          group->bCount++;
          printf("\n");
          return true;
        //resize the lists if necessary then add it to the group
        } else {
          group->bCap *= 2;
          group->bList = (Book **) realloc(group->bList, group->bCap * sizeof( Book *));
          group->bList[group->bCount] = createBook(id, name);
          group->bCount++;
          printf("\n");
          return true;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  //salesperson command
  } else if (strcmp(com, "salesperson") == 0) {
    char id[MAX_NAME + 1] = " ";
    scanf("%s", id);
    //id[MAX_ID] = '\0';
    //check if id is the correct length and if it doesn't already exists in the list
    if (strlen(id) <= MAX_ID && getSalesperson(group, id) == NULL && strlen(id) > 0) {
      char name[MAX_NAME + 1];
      scanf(" %[A-Za-z\' ]s", name);
      if (strlen(name) <= MAX_NAME && strlen(name) > 0) {
        //passes all tests create salesperson and add it to group
        if (group->sCount < group->sCap) {
          group->sList[group->sCount] = createSalesperson(id, name);
          group->sCount++;
          printf("\n");
          return true;
        //resize the lists if necessary then add it to the group
        } else {
          group->sCap *= 2;
          group->sList = (Salesperson **) realloc(group->sList, group->sCap *
                        sizeof( Salesperson *));
          group->sList[group->sCount] = createSalesperson(id, name);
          group->sCount++;
          printf("\n");
          return true;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  //sale command
  } else if (strcmp(com, "sale") == 0) {
    char bk[MAX_ID + 1] = "";
    char sp[MAX_ID + 1] = "";
    int numSold = 0;
    if (scanf("%5s", sp) != 1) {
      return false;
    }
    if (scanf("%5s", bk) != 1) {
      return false;
    }
    if (scanf("%d", &numSold) != 1) {
      return false;
    }
    if (getSalesperson(group, sp) == NULL || getBook(group, bk) == NULL || numSold < 1) {
      return false;
    }
    getBook(group, bk)->sold += numSold;
    getSalesperson(group, sp)->sold += numSold;
    //add book node for the salesperson
    getSalesperson(group, sp)->head = sortInsert( getSalesperson(group, sp)->head,
                                      getBook(group, bk), numSold);
    printf("\n");
    return true;
  //list command
  } else if (strcmp(com, "list") == 0) {
    char lCom[MAX_NAME] = "";
    if (scanf("%s", lCom) != 1) {
      return false;
    }
    if (strcmp(lCom, "books") == 0) {
      printf("\n");
      printf("ID         Name                                Sold\n");
      //sort books
      qsort( group->bList, group->bCount, sizeof(Book *), bookComp);
      int total = 0;
      for ( int i = 0; i < group->bCount; i++) {
        printf("%-10s %-30s %9d\n", group->bList[i]->id, group->bList[i]->name,
              group->bList[i]->sold);
        total += group->bList[i]->sold;
      }
      printf("Total                                     %9d\n", total);
      return true;

    } else if (strcmp(lCom, "salesperson") == 0) {
      printf("\n");
      char id[MAX_ID + 1];
      if (scanf("%s", id) != 1) {
        return false;
      }
      if (getSalesperson(group, id) == NULL) {
        return false;
      }
      int total = 0;
      printf("ID         Name                                Sold\n");
      for ( BookNode *n = getSalesperson(group, id)->head; n; n = n->next ) {
        total += n->sold;
        printf("%-10s %-30s %9d\n", n->book->id, n->book->name, n->sold);
      }
      printf("Total                                     %9d\n", total);
      return true;

    } else if (strcmp(lCom, "group") == 0) {
      printf("\n");
      printf("ID         Name                                Sold\n");
      qsort( group->sList, group->sCount, sizeof(Salesperson *), spComp);
      int total = 0;
      for ( int i = 0; i < group->sCount; i++) {
        printf("%-10s %-30s %9d\n", group->sList[i]->id, group->sList[i]->name,
              group->sList[i]->sold);
        total += group->sList[i]->sold;
      }
      printf("Total                                     %9d\n", total);
      return true;
    } else {
      return false;
    }

  } else if (strcmp(com, "quit") == 0) {
    printf("\n");
    freeGroup(group);
    exit(EXIT_SUCCESS);
  } else {
    freeGroup(group);
    exit(EXIT_SUCCESS);
    return false;
  }
}
