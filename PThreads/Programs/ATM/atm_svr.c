#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Defines
#define MAX_NUM_ACCOUNTS UINT_MAX
#define MAX_NUM_THREADS 10

// Structures
typedef struct {
    int num_active;
    pthread_cond_t thread_exit_cv;
    pthread_mutex_t mutex;
} thread_info_t;

// Data
pthread_mutex_t create_account_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t account_mutex[MAX_NUM_ACCOUNTS];
thread_info_t worker_info;

// Functions
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

    pthread_mutex_lock(&account_mutex[id]);

    /* Retrieve account from database */
    if ((rtn = retrieve_account(id, &accountp)) < 0) {
        sprintf(resp_buf, "%d %s", TRANS_FAILURE, atm_err_tbl[-rtn]);
    }

    pthread_mutex_unlock(&account_mutex[id]);
}

void create_account(char *resp_buf) {
    int id;
    int rtn;
    account_t *accountp;

    pthread_mutex_lock(&create_account_mutex);

    /* Get a new account */
    if ((rtn = new_account(&id, &accountp)) < 0) {
        sprintf(resp_buf, "%d %d %d %s" TRANS_FAILURE, -1, -1, atm_err_tbl[-rtn]);
    }

    pthread_mutex_unlock(&create_account_mutex);
}

void process_request(workorder_t *workorderp) {
    char resp_buff[COMM_BUF_SIZE];
    int trans_id;

    sscanf(workorderp->req_buf, "%d", &trans_id);
    switch (trans_id) {
        case OPEN_ACCT_TRANS:
            open_account(resp_buf);
            break;
    }

    server_comm_send_response(workorderp->conn, resp_buf);

    free(workorderp);

    pthread_mutex_lock(&worker_info.mutex);
    worker_info.num_active--;
    pthread_cond_signal(&worker_info.thread_exit_cv);
    pthread_mutex_unlock(&worker_info.mutex);
}

// Main
int main(int argc, char **argv) {
    workorder_t *workorderp;
    pthread_t *workorder_threadp;
    int conn;
    int trans_id;

    atm_server_init(argc, argv);

    for (;;) {
        /*** Wait for a request ***/
        workorderp = (workorder_t *)malloc(sizeof(workorder_t));
        sever_comm_get_request(&workorderp->conn, workorderp->req_buf);

        /*** Is it a shutdown request? ***/
        sscanf(workorderp->req_buf, "%d", &trans_id);
        if (trans_id == SHUTDOWN) {
            charr resp_buf[COMM_BUF_SIZE];

            pthread_mutex_lock(&worker_info.mutex);

            /* Wait for in-progress requests threads to finish */
            while (worker_info.num_active > 0) {
                pthread_cond_wait(&worker_info.thread_exit_cv, &worker_info.mutex);
            }

            pthread_mutex_unlock(&worker_info.mutex);

            /* process it here with main() thread */
            if (shutdown_req(workorderp->req_buf, resp_buf)) {
                server_comm_send_response(workorderp-conn, resp_buf);
                free(workorderp);
                break;
            }
        }

        /*** Have we exceeded our limit of active threads ? ***/
        pthread_mutex_lock(&worker_info.mutex);
        while (worker_info.num_active == MAX_NUM_THREADS) {
            pthread_cond_wait(worker_info.thread_exit_cv, &worker_info.mutex);
        }
        worker_info.num_active++;
        pthread_mutex_unlock(&worker_info.mutex);

        /*** Spawn a thread to process this request ***/
        pthread_create(worker_threadp, ...);
    }

    server_comm_shutdown();
    return 0;
}
