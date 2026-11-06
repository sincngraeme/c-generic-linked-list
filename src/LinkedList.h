#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedList LinkedList;
typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedListSearchResult LinkedListSearchResult;

struct LinkedListNode {
    LinkedListNode* next;
    LinkedListNode* previous;
};

struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
    size_t size;
};

struct LinkedListSearchResult {
    LinkedListNode* node;
    size_t count;
    bool err;
};

typedef bool (LinkedListPredicate)(LinkedListNode* node, size_t count, void* args);

/**
 * @brief   inserts a node to the LL before the given node
 * @param   self: linked list to insert to 
 * @param   fn: predicate to test each node
 * @param   in: node to insert
 * @return  true on success
 */
bool LinkedList_insert(LinkedList* self, LinkedListNode* new_node, LinkedListNode* location);

/**
 * @brief   appends a node to the end of the LL
 * @param   self: linked list to append to
 */
void LinkedList_append(LinkedList* self, LinkedListNode* new_node);

/**
 * @brief   finds the first node in the LL matching a predicate
 * @param   self: linked list to search
 * @param   fn: predicate to test each node
 * @return  reult.node is valid if result.err == false
 */
LinkedListSearchResult LinkedList_search(
    LinkedList* self, 
    LinkedListPredicate* fn, 
    void* args
);

/**
 * @brief   finds the first node in the LL matching a predicate, starting from a given node
 * @param   self: linked list to search
 * @param   fn: predicate to test each node
 * @return  reult.node is valid if result.err == false
 */
LinkedListSearchResult LinkedList_searchFrom(
    LinkedList* self, 
    LinkedListNode* location,
    LinkedListPredicate* fn, 
    void* args
);

/**
 * @brief   finds the first node in the LL matching a predicate, searching backwards
 * @param   self: linked list to search
 * @param   fn: predicate to test each node
 * @return  reult.node is valid if result.err == false
 */
LinkedListSearchResult LinkedList_searchBackward(
    LinkedList* self, 
    LinkedListPredicate* fn, 
    void* args
);

/**
 * @brief   finds the first node in the LL matching a predicate, searching backwards starting from
 *          a given node
 * @param   self: linked list to search
 * @param   fn: predicate to test each node
 * @return  reult.node is valid if result.err == false
 */
LinkedListSearchResult LinkedList_searchBackwardFrom(
    LinkedList* self, 
    LinkedListNode* location,
    LinkedListPredicate* fn, 
    void* args
);

void LinkedList_remove(LinkedList* self, LinkedListNode* node);

#endif
