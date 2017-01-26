#include <zmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s bind file\n", prog);
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
    if (file) fclose(*file);
}

void free_buffer(void *data, void *hint)
{
    free(data);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        usage(*argv);
    }

    // Is debug?
    const char *fname = argv[2];
    int debug = strcmp(fname, "debug") == 0;

    // Initiate context
    void *ctx __attribute__((cleanup (__raii_zmqctx))) =
        zmq_ctx_new();
    assert(ctx != NULL);

    // Initiate socket
    void *socket __attribute__((cleanup (__raii_zmqsock))) =
        zmq_socket(ctx, ZMQ_PUSH);
    assert(socket != NULL);

    // Bind socket
    int bind_result = zmq_bind(socket, argv[1]);
    if (bind_result == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    // Open file
    FILE *file __attribute__((cleanup (__raii_file))) = NULL;
    if (!debug) {
        file = fopen(argv[2], "r");
        assert(file != NULL);
    }

    //char chunk[4096];
    if (debug) {
        int msg_counter = 1;
        char message[256];

        while (1) {
            sprintf(message, "Message #%d", msg_counter++);
            assert(zmq_send(socket, message, strlen(message), 0) != -1);
            printf("%s sent.\n", message);
            sleep(1);
        }
    } else {
        printf("Send start!\n");
        //char chunk[524288]; // 512kB
        size_t chunk_size = 524288;
        while (!feof(file)) {
            char *chunk = malloc(chunk_size);                
            size_t read = fread(chunk, 1, sizeof(chunk_size), file);

            zmq_msg_t message;
            zmq_msg_init_data(&message,
                chunk,
                read,
                free_buffer,
                NULL);

            assert(zmq_msg_send(&message, socket, 0) != -1);
            //assert(zmq_send(socket, chunk, read, 0) != -1);
        }

        char feofs[] = "__FEOF__";
        //sprintf(chunk, "__FEOF__");
        zmq_send(socket, feofs, strlen(feofs), 0);

        printf("FEOF reached.\n");
    }

    return 0;
}