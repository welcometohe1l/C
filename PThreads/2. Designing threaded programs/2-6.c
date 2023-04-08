// Server (serial)

#include <stdio.h>
#include <stdlib.h>

#define COMM_BUF_SIZE 128

extern int main(int argc, char **argv) {
    char req_buf[COMM_BUF_SIZE];
    char resp_buf[COMM_BUF_SIZE];

    int conn;
    int trans_id;
    int done = 0;

    atm_server_init(argc, argv);

    for(;;) {
        server_comm_get_request(&conn, req_buf);
        sscanf(req_buf, "%d", &trans_id);

        switch(trans_id) {
            case CREATE_ACCT_TRANS:
                create_account(resp_buf);
                break;
            case DEPOSIT_TRANS:
                deposit(req_buf, resp_buf);
                break;
            case WITHDRAW_TRANS:
                withdraw(req_buf, resp_buf);
                break;
            case BALANCE_TRANS:
                balance(req_buf, resp_buf);
                break;
            case SHUTDOWN:
                if (shutdown_req(req_buf, resp_buf)) done = 1;
                break;
            default:
                handle_bad_trans_id(req_buf, resp_buf);
                break;
        }

        server_comm_send_response(conn, resp_buf);

        if (done) break;
    }

    server_comm_shutdown();

    return 0;
}