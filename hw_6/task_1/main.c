#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1000

typedef struct list
{
    char *word;
    struct list *next;
} list;

void printList(list *head)
{
    for (list *i = head; i != NULL; i = i->next)
        printf("%s ", i->word);
    putchar('\n');
}

void printFirstAndLast(list *head)
{
    char *lastWord = head->word;
    while (head)
    {
        if (head->next == NULL)
            printf("first word = %s last word = %s", head->word, lastWord);
        head = head->next;
    }
}

list *insert2(char *value, list *head)
{
    list *res = (list *)calloc(1, sizeof(list));
    int len = strlen(value);
    res->word = malloc(len + 1);
    strcpy(res->word, value);
    res->next = head;
    return res;
}

int main(int argc, char const *argv[])
{
    list *wordList = NULL;
    char word[STR_SIZE] = "";
    int ch = ' ';
    int i = 0;
    while (EOF != (ch = getchar()))
    {
        switch (ch)
        {
        case '.':
        case ' ':
            word[i] = '\0';
            wordList = insert2(word, wordList);
            i = 0;
            break;
        default:
            word[i++] = ch;
            if (i >= STR_SIZE)
                i = 0; 
        }
        if ('.' == ch)
            break;
    }
    // printList(wordList);
    printFirstAndLast(wordList);
    return 0;
}
