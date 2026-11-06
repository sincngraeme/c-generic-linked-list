#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

typedef struct {
    LinkedListNode _;
    int num;
} intLinkedListNode;

// LinkedListPredicate 
typedef struct {
    int num;
} PredicateArgs;

bool LinkdedListPredicate_eq(LinkedListNode* node, size_t count, void* args)
{
    PredicateArgs _args = *(PredicateArgs*)args;
    intLinkedListNode _node = *(intLinkedListNode*)node;
    (void)count;

    return _node.num == _args.num;
}

int main(void) {

    LinkedList list = {0};
    intLinkedListNode* node;

    for(size_t count = 0; count < 10; count++) {
        node = malloc(sizeof(intLinkedListNode));
        node->num = count;
        LinkedList_insert(&list, (LinkedListNode*)node, list.head);
    }

    // print
    for(size_t count = 0; count < 10; count++) {
        LinkedList_remove(&list, (LinkedListNode*)node);
        printf("Node: %d\n", node->num);
    }

    return 0;
}
