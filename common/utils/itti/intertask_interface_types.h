/*******************************************************************************

 Eurecom OpenAirInterface
 Copyright(c) 1999 - 2012 Eurecom

 This program is free software; you can redistribute it and/or modify it
 under the terms and conditions of the GNU General Public License,
 version 2, as published by the Free Software Foundation.

 This program is distributed in the hope it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

 The full GNU General Public License is included in this distribution in
 the file called "COPYING".

 Contact Information
 Openair Admin: openair_admin@eurecom.fr
 Openair Tech : openair_tech@eurecom.fr
 Forums       : http://forums.eurecom.fr/openairinterface
 Address      : EURECOM, Campus SophiaTech, 450 Route des Chappes
 06410 Biot FRANCE

 *******************************************************************************/

/** @defgroup _intertask_interface_impl_ Intertask Interface Mechanisms
 * Implementation
 * @ingroup _ref_implementation_
 * @{
 */

#ifndef INTERTASK_INTERFACE_TYPES_H_
#define INTERTASK_INTERFACE_TYPES_H_

#include <stdint.h>

/* Defines to handle bit fields on unsigned long values */
#define UL_BIT_MASK(lENGTH)             ((1UL << (lENGTH)) - 1UL)
#define UL_BIT_SHIFT(vALUE, oFFSET)     ((vALUE) << (oFFSET))
#define UL_BIT_UNSHIFT(vALUE, oFFSET)   ((vALUE) >> (oFFSET))

#define UL_FIELD_MASK(oFFSET, lENGTH)                   UL_BIT_SHIFT(UL_BIT_MASK(lENGTH), (oFFSET))
#define UL_FIELD_INSERT(vALUE, fIELD, oFFSET, lENGTH)   (((vALUE) & (~UL_FIELD_MASK(oFFSET, lENGTH))) | UL_BIT_SHIFT(((fIELD) & UL_BIT_MASK(lENGTH)), oFFSET))
#define UL_FIELD_EXTRACT(vALUE, oFFSET, lENGTH)         (UL_BIT_UNSHIFT((vALUE), (oFFSET)) & UL_BIT_MASK(lENGTH))

/* Definitions of task ID fields */
#define TASK_THREAD_ID_OFFSET   8
#define TASK_THREAD_ID_LENGTH   8

#define TASK_SUB_TASK_ID_OFFSET 0
#define TASK_SUB_TASK_ID_LENGTH 8

/* Defines to extract task ID fields */
#define TASK_GET_THREAD_ID(tASKiD)          UL_FIELD_EXTRACT(tASKiD, TASK_THREAD_ID_OFFSET, TASK_THREAD_ID_LENGTH)
#define TASK_GET_SUB_TASK_ID(tASKiD)        UL_FIELD_EXTRACT(tASKiD, TASK_SUB_TASK_ID_OFFSET, TASK_SUB_TASK_ID_LENGTH)

/* Defines to shift task ID fields */
#define TASK_SHIFT_THREAD_ID(tHREADiD)      UL_BIT_SHIFT(tHREADiD, TASK_THREAD_ID_OFFSET)
#define TASK_SHIFT_SUB_TASK_ID(sUBtASKiD)   UL_BIT_SHIFT(sUBtASKiD, TASK_SUB_TASK_ID_OFFSET)

#include <messages_types.h>

/* This enum defines messages ids. Each one is unique. */
typedef enum
{
#define MESSAGE_DEF(iD, pRIO, sTRUCT, fIELDnAME) iD,
#include <messages_def.h>
#undef MESSAGE_DEF

    MESSAGES_ID_MAX, MESSAGES_ID_END = MESSAGES_ID_MAX
} MessagesIds;

//! Thread id of each task
typedef enum
{
    THREAD_FIRST = 1, THREAD_NULL = 0,

#define TASK_DEF(tHREADiD, pRIO) THREAD_##tHREADiD,
#define SUB_TASK_DEF(tHREADiD, sUBtASKiD)
#include <tasks_def.h>
#undef SUB_TASK_DEF
#undef TASK_DEF

    THREAD_MAX, THREAD_END = THREAD_MAX,
} thread_id_t;

//! Sub-tasks id, to defined offset form thread id
typedef enum
{
#define TASK_DEF(tHREADiD, pRIO)            SUB_TASK_INIT_##tHREADiD = 0,
#define SUB_TASK_DEF(tHREADiD, sUBtASKiD)   SUB_TASK_OFFSET_##sUBtASKiD,
#include <tasks_def.h>
#undef SUB_TASK_DEF
#undef TASK_DEF
} sub_task_id_t;

//! Tasks id of each task
typedef enum
{
#define TASK_DEF(tHREADiD, pRIO)            tHREADiD = TASK_SHIFT_THREAD_ID(THREAD_##tHREADiD),
#define SUB_TASK_DEF(tHREADiD, sUBtASKiD)   sUBtASKiD = (TASK_SHIFT_THREAD_ID(THREAD_##tHREADiD) | TASK_SHIFT_SUB_TASK_ID(SUB_TASK_OFFSET_##sUBtASKiD)),
#include <tasks_def.h>
#undef SUB_TASK_DEF
#undef TASK_DEF

    TASK_UNKNOWN = 0xFFFF,
} task_id_t;

typedef union msg_s
{
#define MESSAGE_DEF(iD, pRIO, sTRUCT, fIELDnAME) sTRUCT fIELDnAME;
#include <messages_def.h>
#undef MESSAGE_DEF
} msg_t;

#define INSTANCE_DEFAULT    0
#define INSTANCE_ALL        -1

typedef int16_t instance_t;
typedef uint16_t MessageHeaderSize;

/** @struct MessageHeader
 *  @brief Message Header structure for inter-task communication.
 */
typedef struct MessageHeader_s
{
        MessagesIds messageId; /**< Unique message id as referenced in enum MessagesIds */

        task_id_t originTaskId; /**< ID of the sender task */
        task_id_t destinationTaskId; /**< ID of the destination task */
        instance_t instance; /* Task instance for virtualization */

        MessageHeaderSize size; /**< Message size (not including header size) */
} MessageHeader;

/** @struct MessageDef
 *  @brief Message structure for inter-task communication.
 */
typedef struct MessageDef_s
{
        MessageHeader header; /**< Message header */
        msg_t msg; /**< Union of payloads as defined in x_messages_def.h headers */
} MessageDef;

#endif /* INTERTASK_INTERFACE_TYPES_H_ */
/* @} */