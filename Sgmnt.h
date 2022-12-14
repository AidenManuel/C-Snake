struct Sgmnt {
    int x;
    int y;

    struct Sgmnt *next;
    struct Sgmnt *prev;
};

void delTail(struct Sgmnt** head) {
    struct Sgmnt* temp = *head;
    if(*head == NULL)
        return;
    
    if(temp->next == NULL){
        return;
    }

    while(temp->next != NULL){
        *head = NULL;
        temp = temp->next;
    }

    struct Sgmnt* secondLast = temp->prev;

    int deadx, deady;
    deadx = secondLast->next->x;
    deady = secondLast->next->y;
    mvprintw(deadx, deady, "  ");


    secondLast->next = NULL;
    
    free(temp);
    return;
}

struct Sgmnt* slither(struct Sgmnt** head, int new_x, int new_y) {
    // 1. allocate node
    struct Sgmnt* new_head = (struct Sgmnt*)malloc(sizeof(struct Sgmnt));
 
    // 2. put in the data
    new_head->x = new_x;
    new_head->y = new_y;
 
    // 3. Make next of new node as head and previous as NULL
    new_head->next = (*head);
    new_head->prev = NULL;
 
    // 4. change prev of head node to new node
    if ((*head) != NULL)
        (*head)->prev = new_head;
 
    // 5. move the head to point to the new node
    (*head) = new_head;

    // 6. delete the tail
    delTail(head); 
    return new_head;
}

struct Sgmnt* eat(struct Sgmnt** head, int new_x, int new_y) {
    // 1. allocate node
    struct Sgmnt* new_head = (struct Sgmnt*)malloc(sizeof(struct Sgmnt));
 
    // 2. put in the data
    new_head->x = new_x;
    new_head->y = new_y;
 
    // 3. Make next of new node as head and previous as NULL
    new_head->next = (*head);
    new_head->prev = NULL;
 
    // 4. change prev of head node to new node
    if ((*head) != NULL)
        (*head)->prev = new_head;
 
    // 5. move the head to point to the new node 
    (*head) = new_head;
    return new_head;
}

int draw(struct Sgmnt* head) {
    int count = 0;
    while (head != NULL) {
        mvaddch((head)->x, (head)->y, ACS_CKBOARD);
        mvaddch((head)->x, (head)->y + 1, ACS_CKBOARD);
        head = (head)->next;
        count += 1;
    }
    refresh();
    return count;
}

int collide(struct Sgmnt* head) {
    if(head != NULL){
        int testx = head->x;
        int testy = head->y;

        while (head->next != NULL) {
            head = (head)->next;
            if(head->x == testx && head->y == testy)
                return 1;
        }
    }
    return 0;
}