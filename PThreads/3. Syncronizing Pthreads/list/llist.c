#include "llist.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

/* Right now, this routine simply ensures that we dont initialize a list that has data on it */

int llist_init(llist_t *llistp) {
    llistp->first = NULL;
    pthread_rwlock_init(&(llistp->rwlock), NULL);
    return 0;
}

int llist_insert_data(int index, void *datap, llist_t *llistp) {
    llist_node_t *cur, *prev, *new;
    bool found = false;

    pthread_rwlock_wrlock(&(llistp->rwlock));

    for (cur = prev = llistp->first; cur != NULL; prev = cur, cur = cur->nextp) {
        if (cur->index == index) {
            free(cur->datap);
            cur->datap = datap;
            found = true;
            break;
        } else if (cur->index > index) {
            break;
        }
    }

    if (!found) {
        new = (llist_node_t *)malloc(sizeof(llist_node_t));

        new->index = index;
        new->datap = datap;
        new->nextp = cur;

        if (cur == llistp->first) {
            llistp->first = new;
        } else {
            prev->nextp = new;
        }
    }

    pthread_rwlock_unlock(&(llistp->rwlock));

    return 0;
}

int llist_find_data(int index, void **datapp, llist_t *llistp) {
    llist_node_t *cur, *prev, *new;
    bool found = false;

    pthread_rwlock_rdlock(&(llistp->rwlock));

    for (cur = prev = llistp->first; cur != NULL; prev = cur, cur = cur->nextp) {
        if (cur->index == index) {
            free(cur->datap);
        }
    }

    pthread_rwlock_unlock(&(llistp->rwlock));

    return 0;
}