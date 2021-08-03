#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CDataStructures.h>


#define MAX_MESSAGE_LEN 16


struct message_t {
    size_t length;
    char *message;
};

static struct message_t random_message(void) {
    size_t length = rand() % MAX_MESSAGE_LEN;
    if (length == 0)
        length = 1;
#ifdef CDS_DEBUG
    printf("[random_message] length of new message: %zu\n", length);
#endif
    char *message = malloc(length * sizeof(char));
    size_t index = 0;
    for (; index < length - 1; ++index) {
        message[index] = "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
    }
    message[length - 1] = '\0';
    struct message_t object = {
        .length = length,
        .message = message
    };
    return object;
}

static int debug_message(struct message_t *message) {
    return printf(
        "struct message_t {\n"
        "    .length = %zu,\n"
        "    .message = %s\n"
        "}\n",
        message->length,
        message->message
    );
}

static void clean_message(struct message_t *message) {
    if (message == NULL || message->message == NULL)
        return;
    else {
        free(message->message);
        message->message = NULL;
    }
}


int main(int argc, char **argv) {
    printf("Testing dynbuffer.\n");

    srand((uint32_t) time(NULL));

    cds_buffer_t buffer = cds_buffer_new();
    if (buffer == NULL) {
        printf("Could not allocate memory for the buffer.\n");
        return 1;
    } else {
        printf("Memory allocated for blank buffer.\n");
    }
    if (CDS_IS_ERROR(cds_buffer_init(&buffer, sizeof(struct message_t)))) {
        printf("Could not initialise buffer.\n");
    } else {
        printf("Successfully initialised buffer.\n");
    }

    CDS_NEW_STATUS = cds_ok;

    size_t index = 0;

    for (; index < 32; ++index) {
        struct message_t *message = CDS_NEW(struct message_t);
        if (message == NULL) {
            printf("Could not allocate memory for message.\n");
            goto errored;
        }
        *message = random_message();
        debug_message(message);
        status = cds_buffer_push_back(&buffer, message);
        free(message);
        printf("Status: %d\n", status);
        CDS_IF_STATUS_ERROR(status) {
            printf("Could not add message. Index: %zu\n", index);
            goto errored;
        }
    }

    printf("Message successfully put into the buffer.\n");

    goto success;

success:
    cds_buffer_free(buffer, (cds_free_f) clean_message);
    printf("Success.\n");
    return 0;

errored:
    cds_buffer_free(buffer, (cds_free_f) clean_message);
    printf("Errored out.\n");
    return 1;
}
