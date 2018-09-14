/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "MsgProto1"
 * 	found in "/opt/svyazcom/cdr_sca/coren_cpp/protocol/coren.asn1"
 * 	`asn1c -fwide-types`
 */

#ifndef	_AnnounceData_H_
#define	_AnnounceData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MsgAddr.h"
#include <INTEGER.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AnnounceData */
typedef struct AnnounceData {
	MsgAddr_t	 addr;
	INTEGER_t	 priority;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AnnounceData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AnnounceData;

#ifdef __cplusplus
}
#endif

#endif	/* _AnnounceData_H_ */
#include <asn_internal.h>