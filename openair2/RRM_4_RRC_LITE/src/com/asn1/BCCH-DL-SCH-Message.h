/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "/homes/gauthier/PROJETS/OPENAIR4G/openair2/RRM_4_RRC_LITE/src/foreign/generated_c_asn1_rrc/ASN1_files/EUTRA-RRC-Definitions.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types`
 */

#ifndef	_BCCH_DL_SCH_Message_H_
#define	_BCCH_DL_SCH_Message_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BCCH-DL-SCH-MessageType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BCCH-DL-SCH-Message */
typedef struct BCCH_DL_SCH_Message {
	BCCH_DL_SCH_MessageType_t	 message;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BCCH_DL_SCH_Message_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BCCH_DL_SCH_Message;

#ifdef __cplusplus
}
#endif

#endif	/* _BCCH_DL_SCH_Message_H_ */
#include <asn_internal.h>
