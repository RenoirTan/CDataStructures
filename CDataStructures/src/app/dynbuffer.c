#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    --length;
    size_t index = 0;
    for (; index < length; ++index) {
        message[index] = "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
    }
    message[length] = '\0';
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
        printf("Freeing \"%s\"\n", message->message);
        free(message->message);
        message->message = NULL;
    }
}


int main(int argc, char **argv) {
    printf("Testing dynbuffer.\n");

    srand((uint32_t) time(NULL));

    struct message_t *buffer = (struct message_t *) cds_buffer_new();
    if (buffer == NULL) {
        printf("Could not allocate memory for the buffer.\n");
        return 1;
    } else {
        printf("Memory allocated for blank buffer.\n");
    }
    if (CDS_IS_ERROR(cds_buffer_init(
        (cds_buffer_t *) &buffer,
        sizeof(struct message_t)
    ))) {
        printf("Could not initialise buffer.\n");
    } else {
        printf("Successfully initialised buffer.\n");
    }
    printf("Buffer location: %p\n", buffer);

    CDS_NEW_STATUS = cds_ok;
    size_t index = 0;
    struct message_t message;

    for (; index < 32; ++index) {
        message = random_message();
        status = cds_buffer_push_back((cds_buffer_t *) &buffer, &message);
        CDS_IF_STATUS_ERROR(status) {
            printf("Could not add message. Index: %zu\n", index);
            goto errored;
        }
    }

    char *msg = malloc(9 * sizeof(char));
    strcpy(msg, "WILDCARD");
    struct message_t _message = {
        .length = 8,
        .message = msg
    };
    CDS_IF_STATUS_ERROR(cds_buffer_insert(
        (cds_buffer_t *) &buffer,
        5,
        &_message
    )) {
        printf("Could not insert wildcard.\n");
        goto errored;
    }

    struct message_t dumpyard = {0};

    CDS_IF_STATUS_ERROR(cds_buffer_remove(&buffer, 10, &dumpyard)) {
        printf("Could not remove item.\n");
        goto errored;
    } else {
        printf("Removed message at index 10.\n");
        debug_message(&dumpyard);
        clean_message(&dumpyard);
    }

    CDS_IF_STATUS_ERROR(cds_buffer_pop_back(&buffer, &dumpyard)) {
        printf("Could not pop last item.\n");
        goto errored;
    } else {
        printf("Removed last message.\n");
        debug_message(&dumpyard);
        clean_message(&dumpyard);
    }

    printf("Messages successfully piled onto the buffer.\n");

    /*
    for (index = 0; index < cds_buffer_cds_get_length(buffer); ++index) {
        printf("[%zu]: ", index);
        debug_message(&buffer[index]);
    }
    */

    goto success;

success:
    cds_buffer_free(buffer, (cds_free_f)clean_message);
    printf("Success.\n");
    return 0;

errored:
    cds_buffer_free(buffer, (cds_free_f)clean_message);
    printf("Errored out.\n");
    return 1;
}
