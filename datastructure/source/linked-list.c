#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
/**
 * This sample is about how to implement a queue in c
 *
 * Type of item is int
 * Add item to head, tail or any position
 * Get item from head, tail or any position
 * Get and remove item from head, tail or any position
 * Can get the size
 * Can display all item
 */
/**
 * The Node struct,
 * contains item and the pointers that point to previous node/next node.
 */
typedef struct Node {
    int item;
    // previous node
    struct Node* prev;
    // next node
    struct Node* next;
} Node;
/**
 * The LinkedList struct, contains the pointers that
 * point to first node and last node, the size of the LinkedList,
 * and the function pointers.
 */
typedef struct LinkedList {
    Node* head;
    Node* tail;
    // size of this LinkedList
    int size;

    // add item to any position
    void (*add) (struct LinkedList*, int, int);
    // add item after tail
    void (*addLast) (struct LinkedList*, int);
    // add item before head
    void (*addFirst) (struct LinkedList*, int);

    // insert node
    void (*insertBefore) (struct LinkedList*, Node*, Node*);
    // get item from any position
    int (*get) (struct LinkedList*, int);
    // get last item
    int (*getLast) (struct LinkedList*);
    // get first item
    int (*getFirst) (struct LinkedList*);

    // remove item from any position
    int (*remove) (struct LinkedList*, int);
    // remove last item
    int (*removeLast) (struct LinkedList*);
    // remove first item
    int (*removeFirst) (struct LinkedList*);

    // display all element in the LinkedList
    void (*display) (struct LinkedList*);
    // create a node with item
    Node* (*createNode) (int);
} LinkedList;

/** add item to any position
 */
void add (LinkedList* _this, int item, int position);
/** add item to head
 */
void addFirst (LinkedList* _this, int item);
/** add item to tail
 */
void addLast (LinkedList* _this, int item);
/** insert one node before another,
 * newNdoe, node and node->prev should not be null.
 */
void insertBefore (LinkedList* _this, Node* node, Node* newNode);
/** get item from specific position
 */
int get (LinkedList* _this, int position);
/** get item from head
 */
int getFirst (LinkedList* _this);
/** get item from tail
 */
int getLast (LinkedList* _this);
/** get item and remove it from any position
 */
int _remove (LinkedList* _this, int position);
/** get and remove item from head
 */
int _removeFirst (LinkedList* _this);
/** get and remove item from tail
 */
int _removeLast (LinkedList* _this);
/** display the items in the list
 */
void display (LinkedList* _this);
/** create a LinkedList
 */
LinkedList createLinkedList ();
/** create a Node
 */
Node* createNode (int item);

int main () {
    LinkedList list = createLinkedList();

    // 3
    list.addFirst(&list, 3);
    // 3, 5
    list.addLast(&list, 5);
    // 3, 4, 5
    list.add(&list, 4, 1);
    list.display(&list);

    // 3, 4, 5, 6
    list.addLast(&list, 6);
    // 3, 4, 5, 6, 7
    list.addLast(&list, 7);
    list.display(&list);
    printf("Get item: %d\n", list.get(&list, 2));
    printf("Get item: %d\n", list.get(&list, 4));
    list.display(&list);
    // 4, 5, 6, 7
    printf("Remove item: %d\n", list.removeFirst(&list));
    // 4, 5, 6
    printf("Remove item: %d\n", list.removeLast(&list));
    // 4, 6
    printf("Remove item: %d\n", list.remove(&list, 1));
    list.display(&list);

    system("PAUSE");
}
/** add item to any position
 */
void add (LinkedList* _this, int item, int position) {
     // index out of list size
     if (position > _this->size) {
        printf("LinkedList#add: Index out of bound");
        system("PAUSE");
        exit(0);
    }
    // add to head
    if (position == 0) {
        _this->addFirst(_this, item);
    } else if (position == _this->size) {
        // add to tail
        _this->addLast(_this, item);
    } else {
        // insert between head and tail

        Node* node = _this->head;
        int i = 0;
        // loop until the position
        while (i < position) {
            node = node->next;
            i++;
        }
        // insert new node to position
        Node* newNode = _this->createNode(item);
        _this->insertBefore(_this, node, newNode);
        _this->size++;
    }
}
/** add item to head
 */
void addFirst (LinkedList* _this, int item) {
    Node* newNode = _this->createNode(item);
    Node* head = _this->head;
    // list is empty
    if (head == NULL)
        _this->head = newNode;
    else { // has item(s)
        Node* last = _this->tail;
        if (last == NULL) // only head node
            last = head;
        newNode->next = head;
        head->prev = newNode;
        _this->head = newNode;
        _this->tail = last;
    }

    _this->size++;
}
/** add item to tail
 */
void addLast (LinkedList* _this, int item) {
    Node* newNode = _this->createNode(item);
    Node* head = _this->head;
    Node* tail = _this->tail;
    // list is empty
    if (head == NULL)
        _this->head = newNode;
    else { // has item(s)
        Node* lastNode = tail;
        if (tail == NULL) // only head node
            lastNode = head;
        lastNode->next = newNode;
        newNode->prev = lastNode;
        _this->tail = newNode;
    }
    _this->size++;
}

/** insert one node before another,
 * newNdoe, node and node->prev should not be null.
 */
void insertBefore (LinkedList* _this, Node* node, Node* newNode) {
    Node* prev = node->prev;

    node->prev = newNode;
    newNode->next = node;
    prev->next = newNode;
    newNode->prev = prev;
}
/** get item from specific position
 */
int get (LinkedList* _this, int position) {
    // list is empty
    if (_this->size == 0) {
        printf("LinkedList#get: The list is empty.");
        system("PAUSE");
        exit(0);
    } else if (position >= _this->size) {
        // out of bound
        printf("LinkedList#get: Index out of bound");
        system("PAUSE");
        exit(0);
    }
    // get head item
    if (position == 0) {
        return _this->getFirst(_this);
    } else if (position+1 == _this->size) {
        // get tail item
        return _this->getLast(_this);
    } else {
        Node* node = _this->head;
        int i = 0;
        // loop until position
        while (i < position) {
            node = node->next;
            i++;
        }
        return node->item;
    }
}
/** get item from head
 */
int getFirst (LinkedList* _this) {
    // list is empty
    if (_this->size == NULL) {
        printf("LinkedList#getFirst: The list is empty.");
        system("PAUSE");
        exit(0);
    }
    return _this->head->item;
}
/** get item from tail
 */
int getLast (LinkedList* _this) {
    // list is empty
    if (_this->size == 0) {
        printf("LinkedList#getLast: The list is empty.");
        system("PAUSE");
        exit(0);
    }
    // only head node
    if (_this->size == 1) {
        return getFirst(_this);
    }
    return _this->tail->item;
}
/** get item and remove it from any position
 */
int _remove (LinkedList* _this, int position) {
    // list is empty
    if (_this->size == 0) {
        printf("LinkedList#_remove: The list is empty.");
        system("PAUSE");
        exit(0);
    } else if (position >= _this->size) {
        // out of bound
        printf("LinkedList#_remove: Index out of bound");
        system("PAUSE");
        exit(0);
    }

    // remove from head
    if (position == 0) {
        return _this->removeFirst(_this);
    } else if (position+1 == _this->size) {
        // remove from tail
        return _this->removeLast(_this);
    } else {
        Node* node = _this->head;
        Node* prev;
        Node* next;
        int i = 0, item;
        // loop until position
        while (i < position) {
            node = node->next;
            i++;
        }
        item = node->item;
        // remove node from list
        prev = node->prev;
        next = node->next;
        prev->next = next;
        next->prev = prev;
        free(node);
        _this->size--;
        return node->item;
    }
}
/** get and remove item from head
 */
int _removeFirst (LinkedList* _this) {
    Node* head = _this->head;
    Node* next;
    int item;
    // list is empty
    if (head == NULL) {
        printf("LinkedList#_removeFirst: The list is empty.");
        system("PAUSE");
        exit(0);
    }
    item = head->item;
    next = head->next;
    _this->head = next;
    if (next != NULL) // has next item
        next->prev = NULL;
    free(head);
    _this->size--;
    if (_this->size <= 1) // empty or only head node
        _this->tail = NULL;
    return item;
}
/** get and remove item from tail
 */
int _removeLast (LinkedList* _this) {
    // list is empty
    if (_this->size == 0) {
        printf("LinkedList#_removeLast: The list is empty.");
        system("PAUSE");
        exit(0);
    }
    if (_this->size == 1) { // only head node
        return _this->removeFirst(_this);
    } else {
        Node* tail = _this->tail;
        Node* prev = tail->prev;
        int item = tail->item;
        prev->next = NULL;
        if (_this->size > 1)
            _this->tail = prev;
        _this->size--;
        if (_this->size <= 1) // empty or only head node
            _this->tail = NULL;
        return item;
    }
}
/** display the items in the list
 */
void display (LinkedList* _this) {
     int i, size = _this->size;
     if (size == 0)
        printf("no item\n\n");
     else {
        printf("has %d items\n", size);
        Node* node = _this->head;
        for (i = 0; i < size; i++) {
            if (i > 0)
                printf(", ");
            printf("%d", node->item);
            node = node->next;
        }
        printf("\n\n");
    }
}
/** create a LinkedList
 */
LinkedList createLinkedList () {
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.add = &add;
    list.addFirst = &addFirst;
    list.addLast = &addLast;
    list.insertBefore = &insertBefore;
    list.get = &get;
    list.getFirst = &getFirst;
    list.getLast = &getLast;
    list.remove = &_remove;
    list.removeFirst = &_removeFirst;
    list.removeLast = &_removeLast;
    list.display = &display;
    list.createNode = &createNode;
    return list;
}
/** create a Node
 */
Node* createNode (int item) {
    Node* node = (Node*) malloc (sizeof(Node));
    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
