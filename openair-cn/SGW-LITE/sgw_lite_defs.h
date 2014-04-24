/*******************************************************************************
Eurecom OpenAirInterface core network
Copyright(c) 1999 - 2014 Eurecom

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
Forums       : http://forums.eurecom.fsr/openairinterface
Address      : EURECOM,
               Campus SophiaTech,
               450 Route des Chappes,
               CS 50193
               06904 Biot Sophia Antipolis cedex,
               FRANCE
*******************************************************************************/
/*! \file sgw_lite_defs.h
* \brief
* \author Lionel Gauthier
* \company Eurecom
* \email: lionel.gauthier@eurecom.fr
*/

#ifndef SGW_LITE_DEFS_H_
#define SGW_LITE_DEFS_H_



#if defined(ENB_MODE)
# include "UTIL/LOG/log.h"
# define SPGW_APP_ERROR(x, args...) LOG_E(SPGW, x, ##args)
# define SPGW_APP_WARN(x, args...)  LOG_W(SPGW, x, ##args)
# define SPGW_APP_TRACE(x, args...)  LOG_T(SPGW, x, ##args)
# define SPGW_APP_INFO(x, args...) LOG_I(SPGW, x, ##args)
# define SPGW_APP_DEBUG(x, args...) LOG_I(SPGW, x, ##args)
#else
# define SPGW_APP_ERROR(x, args...) do { fprintf(stdout, "[SPGW-APP][E]"x, ##args); } while(0)
# define SPGW_APP_WARN(x, args...)  do { fprintf(stdout, "[SPGW-APP][W]"x, ##args); } while(0)
# define SPGW_APP_TRACE(x, args...)  do { fprintf(stdout, "[SPGW-APP][T]"x, ##args); } while(0)
# define SPGW_APP_INFO(x, args...) do { fprintf(stdout, "[SPGW-APP][I]"x, ##args); } while(0)
# define SPGW_APP_DEBUG(x, args...) do { fprintf(stdout, "[SPGW-APP][D]"x, ##args); } while(0)
#endif


int sgw_lite_init(char* config_file_name_pP);

#endif /* SGW_LITE_DEFS_H_ */