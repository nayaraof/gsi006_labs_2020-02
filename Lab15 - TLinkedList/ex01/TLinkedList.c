#include <stdio.h>
#include "TLinkedList.h"
#include <stdlib.h>

typedef struct list_node list_node;

struct list_node
{
    struct aluno data;
    list_node *next;
};

struct TLinkedList
{
    list_node *head;
};

TLinkedList *list_create()
{
    TLinkedList *list;
    list = malloc(sizeof(TLinkedList));
    if (list != NULL)
    {
        list->head = NULL;
    }
    return list;
}

int list_push_front(TLinkedList *list, struct aluno al)
{
    if (list == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *node;
        node = malloc(sizeof(list_node));
        if (node == NULL)
        {
            return OUT_OF_MEMORY;
        }
        node->data = al;
        node->next = list->head;

        list->head = node;
        return SUCCESS;
    }
}

int list_push_back(TLinkedList *list, struct aluno al)
{
    if (list == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *node;
        node = malloc(sizeof(list_node));
        if (node == NULL)
        {
            return OUT_OF_MEMORY;
        }
        node->data = al;
        node->next = NULL;

        if (list->head == NULL)
        {
            list->head = node;
        }
        else
        {
            list_node *aux;
            aux = list->head;
            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = node;
        }
        return SUCCESS;
    }
}

int list_free(TLinkedList *list)
{
    if (list == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *aux;
        aux = list->head;

        while (aux != NULL)
        {
            list->head = aux->next;
            // list->head = list->head->next;  (outra opção)
            free(aux);
            aux = list->head;
        }
        // segunda forma
        // while (list->head != NULL)
        // {
        //     aux = list->head;
        //     list->head = list->head->next;
        //     free(aux);
        // }

        free(list);
        return SUCCESS;
    }
}

int list_insert_sorted(TLinkedList *list, struct aluno al)
{
    if (list == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *node;
        node = malloc(sizeof(node));
        if (node == NULL)
        {
            return OUT_OF_MEMORY;
        }
        node->data = al;

        list_node *curr; // current - nó atual
        list_node *prev; // previous - nó anterior
        prev = NULL;
        curr = list->head;
        while ((curr != NULL) && curr->data.matricula < al.matricula)
        {
            prev = curr;
            curr = curr->next;
        }
        if (prev == NULL)  // insere na cabeça (lista vazia ou não)
        {
            node->next = list->head;
            list->head = node;
        }
        else
        {// insere a partir do segundo elemento (incluso)
            prev->next = node;
            node->next = curr;
        }
        return SUCCESS;
    }
}
