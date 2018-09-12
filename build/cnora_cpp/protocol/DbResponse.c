/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "CnoraProtocol"
 * 	found in "/opt/svyazcom/cdr_sca/cnora_cpp/protocol/cnora.asn1"
 * 	`asn1c -fwide-types`
 */

#include "DbResponse.h"

static asn_TYPE_member_t asn_MBR_DbResponse_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DbResponse, code),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"code"
		},
	{ ATF_POINTER, 5, offsetof(struct DbResponse, message),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTF8String,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"message"
		},
	{ ATF_POINTER, 4, offsetof(struct DbResponse, dataset),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DbRows,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"dataset"
		},
	{ ATF_POINTER, 3, offsetof(struct DbResponse, params),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DbValues,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"params"
		},
	{ ATF_POINTER, 2, offsetof(struct DbResponse, label),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTF8String,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"label"
		},
	{ ATF_POINTER, 1, offsetof(struct DbResponse, total_rows_num),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"total-rows-num"
		},
};
static const ber_tlv_tag_t asn_DEF_DbResponse_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_DbResponse_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* code */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* message */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* dataset */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* params */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* label */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* total-rows-num */
};
static asn_SEQUENCE_specifics_t asn_SPC_DbResponse_specs_1 = {
	sizeof(struct DbResponse),
	offsetof(struct DbResponse, _asn_ctx),
	asn_MAP_DbResponse_tag2el_1,
	6,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DbResponse = {
	"DbResponse",
	"DbResponse",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_DbResponse_tags_1,
	sizeof(asn_DEF_DbResponse_tags_1)
		/sizeof(asn_DEF_DbResponse_tags_1[0]), /* 1 */
	asn_DEF_DbResponse_tags_1,	/* Same as above */
	sizeof(asn_DEF_DbResponse_tags_1)
		/sizeof(asn_DEF_DbResponse_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DbResponse_1,
	6,	/* Elements count */
	&asn_SPC_DbResponse_specs_1	/* Additional specs */
};

