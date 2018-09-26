/*
* File:   asn_autoexpand_buffer.h
* Author: yurik
*
* Created on 7 Ноябрь 2012 г., 18:53
*/

#ifndef ASN_AUTOEXPAND_BUFFER_H
#define	ASN_AUTOEXPAND_BUFFER_H

#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct asn_autoexpand_buffer_ {
        char *buffer, *ptr;
        size_t size;
    } asn_autoexpand_buffer_t;

    asn_autoexpand_buffer_t *alloc_ae_buffer(size_t base_size);

    int encode_to_ae_buffer_cb(const void *buffer, size_t size, void *key);

    int shift_head_ae_buffer(asn_autoexpand_buffer_t *arg, size_t size);

    size_t size_ae_buffer(asn_autoexpand_buffer_t *arg);

    void free_ae_buffer(asn_autoexpand_buffer_t *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* ASN_AUTOEXPAND_BUFFER_H */

