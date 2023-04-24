#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t global_data_mutex = PTHREAD_MUTEX_INITIALIZER;

void deposit(char *req_buf, char *resp_buf) {
    int rtn;
    int temp, id, password, amount;
    account_t *accountp;

    /* Parse input string */
    sscanf(req_buf, "%d %d %d %d", &temp, &id, &password, &amount);

    /* Check inputs */
    if ((id < 0) || (id >= MAX_NUM_ACCOUNTS)) {
        sprintf(resp_buf, "%d %s", TRANS_FAILURE, ERR_MSG_BAD_ACCOUNT);
        return;
    }

    pthread_mutex_lock(&global_data_mutex);

    /* Retrieve account from database */
    if ((rtn = retrieve_account(id, &accountp)) != 0) {
        sprintf(resp_buf, "%d %s", TRANS_FAILURE, atm_err_tbl[-rtn]);
    }

    pthread_mutex_unlock(&global_data_mutex);
}
