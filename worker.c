#include <zmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s connect output\n", prog);
    exit(1);
}

void __raii_zmqctx(void **ctx)
{
    if (ctx) zmq_ctx_destroy(*ctx);
}

void __raii_zmqsock(void **socket)
{
    if (socket) zmq_close(*socket);
}

void __raii_file(FILE **file)
{
    if (file && *file != stdout) fclose(*file);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        usage(*argv);
    }

    const char *fname = argv[2];
    int to_stdout = strcmp(fname, "stdout") == 0;

    // Initiate context
    void *ctx __attribute__((cleanup (__raii_zmqctx))) =
        zmq_ctx_new();
    assert(ctx != NULL);

    // Initiate socket
    void *socket __attribute__((cleanup (__raii_zmqsock))) =
        zmq_socket(ctx, ZMQ_PULL);
    assert(socket != NULL);

    // Bind socket
    assert(zmq_connect(socket, argv[1]) != -1);

    FILE *file __attribute__((cleanup (__raii_file))) = NULL;
    if (to_stdout) {
        file = stdout;
    } else {
        file = fopen(fname, "w");
    }

    char buffer[524288];
    while (1) {
        int size = zmq_recv(socket, buffer, sizeof(buffer), 0);
        assert(size != -1);

        buffer[size] = 0;
        
        if (strcmp(buffer, "__FEOF__") == 0) {
            printf("End of transmission.\n");
            break;
        }

        fwrite(buffer, 1, size, file);

        if (to_stdout) {
            printf("\n");
            fflush(stdout);
        }
    }

    return 0;
}