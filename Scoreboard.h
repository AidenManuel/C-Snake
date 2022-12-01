struct Player {
    char in1, in2;
    int val, mode;

    struct Player *beeg;
    struct Player *smol;
};

struct Player* createPlayer(int val, char in1, char in2, int mode) {
    struct Player* player = (struct Player*)malloc(sizeof(struct Player));
    player->val = val;
    player->in1 = in1;
    player->in2 = in2;
    player->mode = mode;
    player->beeg = NULL;
    player->smol = NULL;
    return player;
}

void addPlayer(struct Player* newGuy, struct Player* oldFella){
    if (newGuy->val > oldFella->val && (oldFella->beeg == NULL || oldFella->beeg->val > newGuy->val)){
        newGuy->beeg = oldFella->beeg;
        oldFella->beeg = newGuy;
    } else if (newGuy->val > oldFella->val && oldFella->beeg->val < newGuy->val){
        addPlayer(newGuy, oldFella->beeg);
    } else if (newGuy->val < oldFella->val && (oldFella->smol == NULL || oldFella->smol->val < newGuy->val)){
        newGuy->smol = oldFella->smol;
        oldFella->smol = newGuy;
    } else if (newGuy->val < oldFella->val && oldFella->smol->val > newGuy->val){
        addPlayer(newGuy, oldFella->smol);
    } else {
        newGuy->beeg = oldFella->beeg;
        oldFella->beeg = newGuy;
    }
    return;
}

void BEEG2smol(struct Player* gamer){
    FILE* fp = fopen("scores.txt", "a");

    if(gamer->beeg != NULL){
        BEEG2smol(gamer->beeg);
    }
    
    if(gamer->val != 0){
    fprintf(fp, "\n%d   %c%c            %d", gamer->mode, gamer->in1, gamer->in2, gamer->val);
    }

    if(gamer->smol != NULL){
        BEEG2smol(gamer->smol);
    }
    fclose(fp);
}

struct Player* loadFile(struct Player* nullFella){
    int count = 0, mode, val; 
    char in1, in2;
    char str[250];
    FILE* f = fopen("scores.txt", "r");
    while(fgets(str, 250, f) != NULL && count < 19){
            fscanf(f, "%d %c %c %d", &mode, &in1, &in2, &val);
            addPlayer(createPlayer(val, in1, in2, mode), nullFella);
        count++;
    }
    fclose(f);
    return nullFella;
}