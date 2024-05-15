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

list *oddElementRemoval(list *head)
{
    list *p = head;
    while (p->next != NULL)
    {
        if (p->next->next != NULL)
        {
            p->next = p->next->next;
        }
        else if (p->next != NULL)
        {
            p->next->word = NULL;
            p->next = NULL;
            break;
        }
        p = p->next;
    }
    return head;
}

list *insert_end2(char *value, list *head)
{
    list *res = (list *)calloc(1, sizeof(list));
    int len = strlen(value);
    res->word = malloc(len + 1);
    strcpy(res->word, value);
    if (head == NULL)
    {
        return res;
    }
    else
    {
        list *p = head;
        while (p->next != NULL)
            p = p->next;
        p->next = res;
        return head;
    }
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
            wordList = insert_end2(word, wordList);
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
    list *resList = wordList;
    // printList(wordList);
    resList = oddElementRemoval(resList);
    printList(resList);
    return 0;
}
