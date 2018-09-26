/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "MsgProto1"
 * 	found in "/opt/svyazcom/ss7_dmp_cnora/ss7_dmp/coren_cpp/protocol/coren.asn1"
 * 	`asn1c -fwide-types`
 */

#ifndef	_SvcAnnounce_H_
#define	_SvcAnnounce_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include <UTF8String.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AnnounceData;

/* SvcAnnounce */
typedef struct SvcAnnounce {
	INTEGER_t	 announce_timeout;
	UTF8String_t	 hostname;
	struct data {
		A_SEQUENCE_OF(struct AnnounceData) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} data;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SvcAnnounce_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SvcAnnounce;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AnnounceData.h"

#endif	/* _SvcAnnounce_H_ */
#include <asn_internal.h>
