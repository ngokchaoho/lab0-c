#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q != NULL) {
        q->head = NULL;
        q->size = 0;
        q->tail = NULL;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    if (q->head != NULL) {
        list_ele_t *curr_ele = q->head;
        list_ele_t *prev_ele = curr_ele;
        while (curr_ele != NULL) {
            free(curr_ele->value);
            if (curr_ele->next != NULL) {
                curr_ele = curr_ele->next;
            } else {
                free(curr_ele);
                break;
            }
            free(prev_ele);
        }
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    if (q->size == 1)
        q->tail = q->head;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    newt->value = malloc(strlen(s) + 1);
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    newt->next = NULL;
    strncpy(newt->value, s, strlen(s) + 1);
    q->size += 1;
    if (q->size > 1) {
        q->tail->next = newt;
        q->tail = newt;
    } else {
        /*from empty queue*/
        q->head = newt;
        q->tail = newt;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;
    if (sp != NULL) {
        strncat(sp, q->head->value, bufsize - 1);
    }
    list_ele_t *prev_head = q->head;
    q->head = q->head->next;
    free(prev_head->value);
    free(prev_head);
    q->size -= 1;
    if (q->size == 0) {
        q->tail = NULL;
    }
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *curr_ele = q->head;
    list_ele_t *prev_ele = NULL;
    while (curr_ele != q->tail) {
        list_ele_t *next_ele = curr_ele->next;
        curr_ele->next = prev_ele;
        prev_ele = curr_ele;
        curr_ele = next_ele;
    }
    curr_ele->next = prev_ele;
    list_ele_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
