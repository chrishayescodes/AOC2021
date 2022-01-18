#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <assert.h>
using namespace std;

int count_char(char *a_str, const char a_char)
{
    int count = 0;
    char *tmp = a_str;

    while (*tmp)
    {
        if (a_char == *tmp)
        {
            count++;
        }
        tmp++;
    }
    return count;
}

int *str_split(char *a_str, const char a_delim)
{
    int *result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
knows where the list of returned strings ends. */
    count++;

    result = (int *)malloc(sizeof(int) * count);

    if (result)
    {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strtol(token, NULL, 10);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void load_ints(char *line, int *count, int **numbers, char delim)
{
    *count = count_char(line, delim) + 1;
    *numbers = str_split(line, delim);
}

struct node
{
    char *data;
    struct node *next;
};

struct queue
{
    struct node *front, *rear;
};

struct node *newnode(char *data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct queue *createqueue()
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct queue *q, char *data)
{
    struct node *temp = newnode(data);
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

void dequeue(struct queue *q)
{
    if (q->front == NULL)
        return;
    struct node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}

struct card
{
    int data[5][5];
};

int *load_bingoline(char *line)
{
    int *items = (int *)malloc(sizeof(int) * 5);
    int curr = 0;
    for (int i = 0; i < 14; i++)
    {
        if (line[i] != ' ')
        {
            if (line[i + 1] != ' ')
            { // two digits
                char num[2];
                num[0] = line[i];
                num[1] = line[i + 1];
                items[curr] = atoi(num);
                i++;
                curr++;
            }
            else
            {
                char num[1];
                num[0] = line[i];
                items[curr] = atoi(num);
                curr++;
            }
        }
    }
    return items;
}

bool is_winner(int data[5][5], int rw, int col){
    return (data[rw][0] == -1 &&
            data[rw][1] == -1 &&
            data[rw][2] == -1 &&
            data[rw][3] == -1 &&
            data[rw][4] == -1) ||
            (data[0][col] == -1 &&
            data[1][col] == -1 &&
            data[2][col] == -1 &&
            data[3][col] == -1 &&
            data[4][col] == -1);
}

long long get_final_score(int data[5][5], int played){
    int cardsum = 0;
    for(int rw = 0;rw<5;rw++){
        for(int col = 0; col < 5; col++){
            if(data[rw][col] != -1)
                cardsum += data[rw][col];
        }
    }
    return cardsum * played;
}

long long play_game(int *game, int game_item_count, int cardcount, struct card cards[]){
    for(int i = 0; i<game_item_count; i++){
        for(int cardi = 0; cardi < cardcount; cardi++){
            for(int rw = 0; rw<5; rw++){
                for(int col = 0; col<5; col++){
                    if(game[i] == cards[cardi].data[rw][col])
                        cards[cardi].data[rw][col] = -1;
                    if(is_winner(cards[cardi].data, rw, col)){
                        return get_final_score(cards[cardi].data, game[i]);
                        
                    }
                }
            }
        }
    }
    return -1;
}

void load_cards(int cardcount, struct queue *queue, struct card cards[]){
    for (int c = 0; c < cardcount; c++)
    {
        printf("loading card number %d\n", c + 1);
        struct card *newcard =
            (struct card *)malloc(sizeof(card));
        for (int i = 0; i < 5; i++)
        {
            dequeue(queue);
            int count;
            int *bingoline = load_bingoline(queue->front->data);
            memcpy(newcard->data[i], bingoline, sizeof(newcard->data[i]));
        }
        cards[c] = *newcard;
        // dump split lines
        dequeue(queue);
    }
}

bool load_game(int *game, int *game_item_count, int *linecount, struct queue *queue){
    
    std::ifstream file("./files/input.txt");

    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);

    char *charline = new char[line.length() + 1];
    strcpy(charline, line.c_str());
    load_ints(charline, &*game_item_count, &game, ',');
    printf("create queue");
    while (std::getline(file, line))
    {
        char *data = new char[line.length() + 1];
        strcpy(data, line.c_str());
        printf("enqueing: %s\n", data);
        enqueue(queue, data);
        *linecount++;
    }
    file.close();
    return true;
}

int main()
{
    int game_item_count;
    int *game;
    int linecount = 0;
    struct queue *queue = createqueue();

    if(!load_game(game, &game_item_count, &linecount, queue)){
        printf("ERROR: unable to load game");
        return -1;
    }

    int cardcount = linecount / 6; //five lines per game plus splitter line
    struct card cards[cardcount];

    printf("loading cards into buffers\n");
    load_cards(cardcount, queue, cards);

    long long finalscore = play_game(game, game_item_count, cardcount, cards);
    printf("final score: %lld\n", finalscore);

    return 0;
}