/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "/homes/gauthier/PROJETS/OPENAIR4G/openair2/RRM_4_RRC_LITE/src/foreign/generated_c_asn1_rrc/ASN1_files/EUTRA-RRC-Definitions.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types`
 */

#ifndef	_SecurityModeComplete_r8_IEs_H_
#define	_SecurityModeComplete_r8_IEs_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SecurityModeComplete-r8-IEs */
typedef struct SecurityModeComplete_r8_IEs {
	struct SecurityModeComplete_r8_IEs__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SecurityModeComplete_r8_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SecurityModeComplete_r8_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _SecurityModeComplete_r8_IEs_H_ */
#include <asn_internal.h>
