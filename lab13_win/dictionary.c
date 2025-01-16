/* SYSC 2006 - Lab 13 - ADT dictionary/map implemented using a hashtable.
 *
 */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

/* Helper functions. */

/* The strdup function is not part of the C standard library in C11 and C17, but will
 * be included in C2x. For earlier versions of C, some compilers provide this function 
 * as an extension to the standard library. 
 *
 * If this function causes a compilation/linking error, it's likely because your compiler
 * compiler is configured to use the C2x standard or provides extensions to C11/C17.
 *
 * 1. You can comment-out the function and reconfigure your compiler to use C2x.
 * (In Pelles C, select Project > Project Options..., click Compiler, then select C2X from 
 * from the C standard drop-down menu.)
 *
 * 2. Or, you can leave the function as-is, reconfigure your compiler to use C17, and  
 * disable any extensions that provide strdup. 
 *
 * Create a duplicate of s on the heap and return the pointer to it.
 * Return NULL if space can't be allocated.
 */
static char *my_strdup(char *s)
{
    char *p = malloc(strlen(s) + 1);  // +1 for '\0'
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/* Return the hash value for string s. */
static unsigned hash(char *s)
{
    unsigned int hashvalue;

    for (hashvalue = 0; *s != '\0'; s += 1) {
        hashvalue = *s + 31 * hashvalue;
    }
    return hashvalue % TABLESIZE;
}

/* If key is found in the linked list pointed to by head, return a
 * pointer to the entry that contains key; otherwise return NULL.
 */
static entry_t *search(entry_t *head, char *key)
{
    for (entry_t *entry = head; entry != NULL; entry = entry->next) {
        if (strcmp(key, entry->key) == 0) {
            return entry;  // key found
        }
    }
    return NULL;
}

/*-----------------------------------------------------------------*/

/* Allocate a new dictionary on the heap and return a pointer to it.
 * Terminate via assert if the dictionary can't be allocated.
 */
dict_t *make_dictionary(void)
{
    dict_t *hashtable = malloc(sizeof(entry_t *) * TABLESIZE);
    assert(hashtable != NULL);

    // Each slot in the table stores the pointer to a chain
    // (a linked list). Initially, all chains are empty.
    for (int i = 0; i < TABLESIZE; i += 1) {
        hashtable[i] = NULL;
    }
    return hashtable;
}

/* If key is found in dictionary dict, return the value associated with 
 * the key; otherwise return NULL.
 */
char *get(dict_t *dict, char *key)
{
    unsigned hashvalue = hash(key);
    entry_t *entry = search(dict[hashvalue], key);
    if (entry != NULL) {
        return entry->value;  // key found
    }
    return NULL;
}

/* Insert (key, value) in dictionary dict. If key is already in the 
 * dictionary, replace the value currently associated with key.
 * Terminate via assert if memory couldn't be allocated while
 * updating the dictionary.
 */
void put(dict_t *dict, char *key, char *value)
{
    unsigned hashvalue = hash(key);
    entry_t *entry = search(dict[hashvalue], key);
    if (entry == NULL) { 
        // key not found, so add key/value in a new entry in the chain.
        entry = malloc(sizeof(entry_t));
        assert(entry != NULL);
        entry->key = my_strdup(key);
        assert(entry->key != NULL);

        // Insert the new entry at the front of the linked list.
        entry->next = dict[hashvalue];
        dict[hashvalue] = entry;
    } else {  
        // The key is already in the table, so just replace the
        // current value with the new one.
        free(entry->value);  // Deallocate the current value
    }

    // Put the value associated with the key in the entry.
    entry->value = my_strdup(value);
    assert(entry->value != NULL);
}

//EXCERCISES 

/* Print the dictionary pointed to by dict, using the format:
0: key_0: value_0, key_1: value_1, ...
1: key_0: value_0, key_1: value_1, ...
...
n-1: key_0: value_0, key_1: value_1, ...
*/
void print_dictionary(dict_t *dict)
{
    for(int i=0; i < TABLESIZE; i++){
        printf("\n %d: ", i);
        if(dict[i]==NULL){
            printf("NULL");
        }
        for(entry_t *entry = dict[i]; entry!=NULL; entry=entry->next){
            printf("%s: %s", entry->key, entry->value);
            if(entry->next!=NULL){
                printf(", ");
            }
        }
    }
}

/* If key is in the dictionary, replace its associated value with
* a copy of the string pointed to by value, and return true.
* If key is not in the dictionary, return false to indicate that
* the dictionary has not changed.
* Terminate via assert if memory could not be allocated while
* updating the dictionary.
*/

/*
_Bool replace(dict_t *dict, char *key, char *value)
{
    for(int i=0; i < TABLESIZE; i++){
        entry_t *update = search(dict[i], key);
        if(update!=NULL){
            free(update->value);
            update->value = my_strdup(value);
            assert(update->value!=NULL);
            return true;
        }
    }
    return false;
}
*/

_Bool replace(dict_t *dict, char *key, char *value){
    int index = hash(key);
    entry_t *entry = search(dict[index], key);
    if(entry==NULL){
        return false;
    }
    entry->value=my_strdup(value);
    return true;
}

/* Remove all the key/value entries from the dictionary.
* The dictionary will be empty after this call returns.
*/

/*
void clear(dict_t *dict)
{
    assert(dict!=NULL);
    entry_t *next;
    for(int i=0; i<TABLESIZE; i++){
        while(dict[i]!=NULL){
            next=dict[i]->next;
            free(dict[i]);
            dict[i]=next;
        }
        dict[i]=NULL;
    }

}
*/

/*
void clear(dict_t *dict){
    for(int i = 0; i < TABLESIZE; i++){
        entry_t *temp = dict[i];
        while(temp!=NULL){
            dict[i]=temp->next;
            free(temp);
            temp=dict[i];
        }
        dict[i]=NULL;
    }
}
*/

void clear(dict_t *dict){
    for(int i = 0; i < TABLESIZE; i++){
        for(entry_t *temp=dict[i]; temp!=NULL; temp=dict[i]){
            dict[i]=temp->next;
            free(temp);
        }
    }
}