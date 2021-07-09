#include <stdio.h>
#include <stdlib.h>
#include <CDataStructures/stack.h>


int64_t check_brackets(char *pointer) {
    printf("Location of string: %p\n", pointer);
    cds_stack_t *stack = cds_stack_new();
    if (stack == NULL) {
        printf("Could not allocate memory for Stack.\n");
        return -2;
    }
    if (CDS_IS_ERROR(cds_stack_init(stack))) {
        printf("Could not initialise stack.\n");
        goto errored;
    }
    printf("Stack initialised.\n");

    int64_t index;

    for (index = 0; pointer[index] != '\0'; ++index) {
        printf("Current index: %lli\n", index);
        char *top = cds_stack_top(stack);
        if (cds_stack_is_empty(stack)) {
            printf("The stack is empty.\n");
            cds_stack_push(stack, pointer);
            continue;
        } else if (top == NULL) {
            printf("Could not get top character.\n");
            goto errored;
        } else {
            printf("Top character pointer: %p\n", top);
            printf("Top character: %c\n", *top);
        }
        printf("Current character: %c\n", *top);
        switch (pointer[index]) {
            case '(':
            case '[':
            case '{':
                if (CDS_IS_ERROR(cds_stack_push(stack, pointer + index))) {
                    goto errored;
                }
                break;
#define D(l, r)                                         \
    case r:                                             \
        if (*top != l) {                                \
            goto discrepancy;                           \
        }                                               \
        if (CDS_IS_ERROR(cds_stack_pop(stack, NULL))) { \
            goto errored;                               \
        }                                               \
        break;

            D('(', ')')
            D('[', ']')
            D('{', '}')

#undef D
            default:
                goto errored;
        }
    }

    cds_stack_free(stack, NULL);
    return -1;

    discrepancy:
    cds_stack_free(stack, NULL);
    return index;

    errored:
    cds_stack_free(stack, NULL);
    return -2;
}


int main(int argc, char **argv) {
    printf("Testing Stack.\n");
    char buffer[] = "((((((())))){}{{}}))";
    printf("Checking if '%s' is syntactically correct.\n", buffer);
    int64_t loc = check_brackets(buffer);
    if (loc == -1) {
        printf("No discrepancies!.\n");
    } else if (loc == -2) {
        printf("An error occurred.\n");
    } else if (loc >= 0) {
        printf("Bad character at index %lli\n", loc);
    } else {
        printf("Unknown status code: %lli\n", loc);
    }
}
