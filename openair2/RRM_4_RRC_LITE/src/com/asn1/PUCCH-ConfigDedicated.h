/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "/homes/gauthier/PROJETS/OPENAIR4G/openair2/RRM_4_RRC_LITE/src/foreign/generated_c_asn1_rrc/ASN1_files/EUTRA-RRC-Definitions.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types`
 */

#ifndef	_PUCCH_ConfigDedicated_H_
#define	_PUCCH_ConfigDedicated_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <NULL.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PUCCH_ConfigDedicated__ackNackRepetition_PR {
	PUCCH_ConfigDedicated__ackNackRepetition_PR_NOTHING,	/* No components present */
	PUCCH_ConfigDedicated__ackNackRepetition_PR_release,
	PUCCH_ConfigDedicated__ackNackRepetition_PR_setup
} PUCCH_ConfigDedicated__ackNackRepetition_PR;
typedef enum PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor {
	PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor_n2	= 0,
	PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor_n4	= 1,
	PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor_n6	= 2,
	PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor_spare1	= 3
} e_PUCCH_ConfigDedicated__ackNackRepetition__setup__repetitionFactor;
typedef enum PUCCH_ConfigDedicated__tdd_AckNackFeedbackMode {
	PUCCH_ConfigDedicated__tdd_AckNackFeedbackMode_bundling	= 0,
	PUCCH_ConfigDedicated__tdd_AckNackFeedbackMode_multiplexing	= 1
} e_PUCCH_ConfigDedicated__tdd_AckNackFeedbackMode;

/* PUCCH-ConfigDedicated */
typedef struct PUCCH_ConfigDedicated {
	struct PUCCH_ConfigDedicated__ackNackRepetition {
		PUCCH_ConfigDedicated__ackNackRepetition_PR present;
		union PUCCH_ConfigDedicated__ackNackRepetition_u {
			NULL_t	 release;
			struct PUCCH_ConfigDedicated__ackNackRepetition__setup {
				long	 repetitionFactor;
				long	 n1PUCCH_AN_Rep;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ackNackRepetition;
	long	*tdd_AckNackFeedbackMode	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PUCCH_ConfigDedicated_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_repetitionFactor_5;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_tdd_AckNackFeedbackMode_11;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PUCCH_ConfigDedicated;

#ifdef __cplusplus
}
#endif

#endif	/* _PUCCH_ConfigDedicated_H_ */
#include <asn_internal.h>
