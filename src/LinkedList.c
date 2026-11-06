/**
 * @file    LinkedList.c: type generic linked list implementation with no hidden allocations 
 * @authors Nigel Sinclair
 */

#include "LinkedList.h"
#include <assert.h>

typedef enum {
    LINKED_LIST_SEARCH_FORWARD,
    LINKED_LIST_SEARCH_BACKWARD,
    LINKED_LIST_SEARCH_FORWARD_FROM,
    LINKED_LIST_SEARCH_BACKWARD_FROM,
} LinkedListSearchType;

bool LinkedList_insert(
    LinkedList* self, 
    LinkedListNode* new_node,
    LinkedListNode* location
) {
    assert(self);
    if(!new_node || !location) return false;

    // if list is empty initialize
    if(self->head == NULL) {
        self->head = new_node;
        self->head->previous = NULL;
        self->tail = new_node;
        self->tail->next = NULL;
        return false;
    }

    // if location == head
        // 1.   A ...
        // 2.   0 <- B  A/H
        // 3.   0 <- B -> A/H
        // 4.   0 <- B <-> A/H
        // 5.   0 <- B/H <-> A
    // if location != head
        // 1.   A <-> B
        // 2.   C -> A <-> B
        // 3.   A <-> B
        //      ^- C -^
        // 4.   A <- C <-> B
        // 5.   A <-> C <-> B

    // if location is head then location->previous is NULL
    new_node->previous = location->previous; 
    new_node->next = location;
    location->previous = new_node;

    if(location == self->head) {
        self->head = new_node;
    } else {
        new_node->previous->next = new_node;
    }

    self->size++;

    return true;
}

void LinkedList_append(LinkedList* self, LinkedListNode* new_node) {
    assert(self);
    assert(new_node);

    if(self->head == NULL) {
        // list empty
        self->head = new_node;
        self->tail = new_node;
        self->tail->next = NULL;
        self->head->previous = NULL;
    }
    
    self->tail->next = new_node;
    self->tail = new_node;
    self->tail->next = NULL;
    self->size++;
}


static LinkedListSearchResult LinkedList_search_exp(
    LinkedList* self, 
    LinkedListNode* location,
    LinkedListPredicate* fn, 
    void* args,
    LinkedListSearchType search_type
) {
    assert(self);
    assert(fn);

    LinkedListNode* current = NULL;
    int direction = 0;
    size_t index = 0; 

    // set search parameters
    switch(search_type) {
        case LINKED_LIST_SEARCH_FORWARD: 
            direction = 1;
            current = self->head;
            break;
        case LINKED_LIST_SEARCH_FORWARD_FROM: 
            direction = 1;
            current = location;
            break;
        case LINKED_LIST_SEARCH_BACKWARD: 
            direction = -1;
            current = self->tail;
            break;
        case LINKED_LIST_SEARCH_BACKWARD_FROM: 
            direction = -1;
            current = location;
            break;
        default:
            goto not_found;
    };

    while(current != NULL && !fn(current, index, args)) {
        current = current->next;
        index += direction;
    }
        
    if(index == self->size || current == self->tail || current == NULL) goto not_found;

// found:
    return (LinkedListSearchResult){ 
		.count = index, 
		.err = false, 
		.node = current, 
    };
not_found:
    return (LinkedListSearchResult){ 
        .count = index, 
        .err = true, 
        .node = NULL,
    };
}

LinkedListSearchResult LinkedList_search(LinkedList* self, LinkedListPredicate* fn, void* args) {
    return LinkedList_search_exp(self, NULL, fn, args, LINKED_LIST_SEARCH_FORWARD);
}

LinkedListSearchResult LinkedList_searchFrom(
    LinkedList* self, 
    LinkedListNode* location,
    LinkedListPredicate* fn, 
    void* args
) {
    return LinkedList_search_exp(self, location, fn, args, LINKED_LIST_SEARCH_FORWARD_FROM);
}

LinkedListSearchResult LinkedList_searchBackward(
    LinkedList* self, 
    LinkedListPredicate* fn, 
    void* args
) {
    return LinkedList_search_exp(self, NULL, fn, args, LINKED_LIST_SEARCH_BACKWARD);
}

LinkedListSearchResult LinkedList_searchBackwardsFrom(
    LinkedList* self, 
    LinkedListNode* location,
    LinkedListPredicate* fn, 
    void* args
) {
    return LinkedList_search_exp(self, location, fn, args, LINKED_LIST_SEARCH_BACKWARD);
}

void LinkedList_remove(LinkedList* self, LinkedListNode* node) {
    assert(self);
    assert(node);

    // empty list
    if(self->head == NULL) return;

    if(node->next) {
        node->next->previous = node->previous;
    }

    if(node->previous) {
        node->previous->next = node->next;
    }

    if(node == self->head) {
        self->head = node->next;
        return;
    }

    if(node == self->tail) {
        self->tail = node->previous;
        return;
    }
}
