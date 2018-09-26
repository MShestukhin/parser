#include "asn_autoexpand_buffer.h"
#include <string.h>
#include <stddef.h>

asn_autoexpand_buffer_t *alloc_ae_buffer(size_t base_size)
{
    asn_autoexpand_buffer_t *res = (asn_autoexpand_buffer_t *)malloc(sizeof(asn_autoexpand_buffer_t));
    if (!res) {
        res = NULL;
        return res;
    }

    memset(res, 0, sizeof(asn_autoexpand_buffer_t));
    res->ptr = res->buffer = malloc(res->size = base_size);
    if (!res->buffer) {
        free(res);
        res = NULL;
    }
    return res;
}

int encode_to_ae_buffer_cb(const void *buffer, size_t size, void *key)
{
    asn_autoexpand_buffer_t *arg = (asn_autoexpand_buffer_t *)key;

    ptrdiff_t pdiff = arg->ptr - arg->buffer;
    if((arg->size - pdiff) < size) {
        void *new_p = realloc(arg->buffer, arg->size + size);
        if (new_p) {
            arg->buffer = new_p;
            arg->ptr = arg->buffer + pdiff;
            arg->size += size;
        } else {
            return -1;
        }
    }

    memcpy(arg->ptr, buffer, size);
    arg->ptr = ((char *)arg->ptr) + size;

    return 0;
}

int shift_head_ae_buffer(asn_autoexpand_buffer_t *arg, size_t size)
{
    if (arg == NULL)
        return -1;
    if (size) {
        if (((ptrdiff_t)size) > (arg->ptr - arg->buffer))
            return -1;
        memmove(arg->buffer, arg->buffer + size, (arg->ptr - arg->buffer) - size);
        arg->ptr -= size;
    }
    return 0;
}

size_t size_ae_buffer(asn_autoexpand_buffer_t *arg)
{
    if (!arg)
        return 0;

    return arg->ptr - arg->buffer;
}

void free_ae_buffer(asn_autoexpand_buffer_t *arg)
{
    free(arg->buffer);
    free(arg);
}

