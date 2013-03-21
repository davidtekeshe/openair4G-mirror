/*******************************************************************************

  Eurecom OpenAirInterface
  Copyright(c) 2012 Eurecom - THALES Communications & Security

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
  Address      : 

*******************************************************************************/

/*! \file virtual_link.c
* \brief primitives to establish and manage the virtual link 
* \author Philippe Agostini and navid nikaein 
* \date 2012
* \version 0.1
* @ingroup _mac
*/


#include "defs.h"
#include "extern.h"
#include "PHY/extern.h"
#include "UTIL/LOG/log.h"
#include "RRC/L2_INTERFACE/openair_rrc_L2_interface.h"
#include "RRC/LITE/defs.h"

#include "virtual_link.h" 
//extern eNB_MAC_INST *eNB_mac_inst; 
//extern UE_MAC_INST *UE_mac_inst; 

extern inline unsigned int taus(void);

/********************
 * Global variables *
 ********************/

struct virtual_links vlinksTable[NB_MAX_CH];
struct forwarding_Table forwardingTable[NB_MAX_CH];
//struct cornti_array corntis;

//LOLAmesh
void vlink_init(u8 nb_connected_eNB, u8 nb_vlink_eNB, u8 nb_ue_per_vlink){
  int i,j,k;
  LOG_D(MAC,"[eNB][VLINK] initilizing ... \n");  
  for (i=0; i< NB_eNB_INST;i++ ){ 
    vlinksTable[i].count = nb_vlink_eNB; // Nb of virtual links
    for (j=0; j < nb_vlink_eNB; j++) {
      vlinksTable[i].array[j].vlinkID = j+1; 
      vlinksTable[i].array[j].PCellIddestCH = 1; // dummy value
      vlinksTable[i].array[j].PCellIdsourceCH = 2; // dummy value
      vlinksTable[i].array[j].status = VLINK_NOT_CONNECTED; // Virtual link state
      vlinksTable[i].array[j].MRarray.count = nb_ue_per_vlink; // Nb of MRs in the virtual link
      for (k=0; k<nb_ue_per_vlink; k++ ) {
	vlinksTable[i].array[j].MRarray.array[k] = k; 
      }
    }
  }
  
  /*
  // Virtual links table initialization 
  // CH 0 = eNB 0 = Mod_id 0 => vlinksTable index
  // CH 1 = eNB 1 = Mod_id 1
  // 1 virtual link to be defined with 1 MRs => vlinksTable.array index
  // MR 0 = UE 0 = UE_index 0 => vlinksTable.array.MRarray.array index
  vlinksTable[0].count = 1; // Nb of virtual links
  vlinksTable[0].array[0].vlinkID = 1; // Virtual link ID
  vlinksTable[0].array[0].PCellIddestCH = 1; // dummy value
  vlinksTable[0].array[0].PCellIdsourceCH = 2; // dummy value
  vlinksTable[0].array[0].status = VLINK_NOT_CONNECTED; // Virtual link state
  vlinksTable[0].array[0].MRarray.count = 1; // Nb of MRs in the virtual link
  vlinksTable[0].array[0].MRarray.array[0] = 0; // UE_index of the MR
  //vlinksTable[0].array[0].MRarray.array[1] = 1; // UE_index of the MR

  // vlinksTable[1].count = 1; // Nb of virtual links
  vlinksTable[1].array[0].vlinkID = 1; // Virtual link ID
  vlinksTable[1].array[0].PCellIddestCH = 1; // dummy value
  vlinksTable[1].array[0].PCellIdsourceCH = 2; // dummy value
  vlinksTable[1].array[0].status = VLINK_NOT_CONNECTED; // Virtual link state
  vlinksTable[1].array[0].MRarray.count = 1; // Nb of MRs in the virtual link
  vlinksTable[1].array[0].MRarray.array[0] = 0; // UE_index of the MR
  vlinksTable[1].array[0].MRarray.array[0] = 1; // UE_index of the MR

  */

  /* CORNTIs tables initialization */
  for (i=0;i<NB_eNB_INST;i++) {
    for (j=0;j<NB_UE_INST;j++) {
      //MAC layer structure
      eNB_mac_inst[i].UE_template[j].corntis.count = 0;
      UE_mac_inst[j].corntis.count = 0;
      //PHY layer structure
      PHY_vars_eNB_g[i]->dlsch_eNB[j][0]->corntis.count = 0;
      PHY_vars_UE_g[j]->dlsch_ue[i][0]->corntis.count = 0;
    }
  }
  
}

int  vlink_setup(u8 Mod_id, u32 frame, u8 subframe ){
  
  int i, j;
  u16 UE_index = 0;
  u8 vlink_status = 1;
  u16 cornti;
  u8 vlid;
  u8 status=VLINK_NOT_CONNECTED;
  u8 nb_corntis; //length of the cornti array
   
  LOG_D(MAC,"[eNB %d][VLINK] Frame %d, Subframe %d, check for collaborative DRB\n",Mod_id, frame, subframe);
   /* We go through the virtual links of the table */
  for (i=0;i<vlinksTable[Mod_id].count;i++){ // end for (i=0;i<vlinksTable[Mod_id].count;i++)
    
    /* If the VL has not been established yet, try to establish it */
    if (vlinksTable[Mod_id].array[i].status == VLINK_NOT_CONNECTED) {
      
      /* Get the virtual link ID */
      vlid = vlinksTable[Mod_id].array[i].vlinkID;
      
      LOG_D(MAC,"[eNB %d][VLINK] Frame %d, Subframe %d, VLINK %d not connected\n",Mod_id, frame, subframe, vlid);
      
      /* We go through all the MRs belonging to a VL */
      for (j=0;j<vlinksTable[Mod_id].array[i].MRarray.count;j++) {
	
	/* We get the ID of the MR */
	UE_index = vlinksTable[Mod_id].array[i].MRarray.array[j];
	
	/* If the default RB is not active for this MR */
	/* We can't establish a RB */
	status = mac_get_rrc_status(Mod_id,1,UE_index);
	if (status != RRC_RECONFIGURED) {
	  LOG_D(MAC,"[eNB %d][VLINK] Frame %d, Subframe %d, VLINK %d UE %d in RRC_IDLE (%d), can't establish virtual link\n",
		Mod_id, frame, subframe, vlid, UE_index,status);
	  vlink_status = 0;
	  break;
	}
	
      }// end for(j=0;j<vlinksTable[Mod_id].array[i].MRarray.count;j++)
      
      /* If the VL is ready to be established */
      if (vlink_status == 1) {
	
	LOG_D(MAC,"[eNB %d][VLINK] Frame %d, Subframe %d, VLINK %d ready to be established\n",Mod_id, frame, subframe, vlid);
	/* We chose the cornti randomly */
	  cornti = (u16)taus();
	  
	  /* Keep track of the CORNTI */
	  //MAC layer structure
	  nb_corntis = eNB_mac_inst[Mod_id].UE_template[UE_index].corntis.count;
	  eNB_mac_inst[Mod_id].UE_template[UE_index].corntis.array[nb_corntis] = cornti;
	  eNB_mac_inst[Mod_id].UE_template[UE_index].corntis.count++;
	  //PHY layer structure
	  nb_corntis = PHY_vars_eNB_g[Mod_id]->dlsch_eNB[UE_index][0]->corntis.count;
	  PHY_vars_eNB_g[Mod_id]->dlsch_eNB[UE_index][0]->corntis.array[nb_corntis] = cornti;
	  PHY_vars_eNB_g[Mod_id]->dlsch_eNB[UE_index][0]->corntis.count++;
	  
	  /* For all the MR of the VL we establish a CO-DRB */
	  for (j=0;j<vlinksTable[Mod_id].array[i].MRarray.count;j++) {

	    /* We get the UE_index of the MR */
	    UE_index = vlinksTable[Mod_id].array[i].MRarray.array[j];
	    
	    // Generate and send RRCConnectionReconfiguration
	    rrc_eNB_generate_RRCConnectionReconfiguration_co(Mod_id,UE_index,frame,cornti,vlid);
	    
	  }// end for (j=0;j<vlinksTable[Mod_id].array[i].MRList.count;j++)
	  
	  /* We mark the virtual link as established */
	  vlinksTable[Mod_id].array[i].status = VLINK_CONNECTED;
	  
	}// end if (vlink_status == 1)
      status = vlinksTable[Mod_id].array[i].status;
      }// end if (vlinksTable.table[i].status == VLINK_NOT_CONNECTED)
      
      /* Else go to the next VL */
      else {
	LOG_D(MAC,"[eNB %d][VLINK] Frame %d, Subframe %d, VLINK %d connected\n",Mod_id, frame, subframe, vlinksTable[Mod_id].array[i].vlinkID);
	break;
      }
      
    }

  return status; // vlinksTable[Mod_id].array[i].status;
}




/* Add a new entry or fill a new entry in the forwarding table
 * returns 0 = entry added / -1 = error */
int mac_forwarding_add_entry(u8 Mod_id,
			     u8 eNB_index,
			     u8 vlid,
			     u16 cornti) {
  
  int ret = 0;
  int i = 0;
  int existing_entry = 0;
  u8 current_vlid = 0;
  
  /* We look for an existing entry */
  while ((i<forwardingTable->count) && (current_vlid != vlid)) {
    
    current_vlid = forwardingTable->array[i].vlid;
    
    /* We ve found it */
    if (current_vlid == vlid) {
      
      /* We fill the cornti which has an error value */
      if (forwardingTable->array[i].cornti1 == 0) {
	forwardingTable->array[i].cornti1 = cornti;
	existing_entry = 1;
      }
      
      if (forwardingTable->array[i].cornti2 == 0) {
	forwardingTable->array[i].cornti2 = cornti;
	existing_entry = 1;
      }
      
      LOG_I(MAC,"[CONFIG][UE %d][TCS DEBUG] Configuring MAC forwarding table from eNB %d, existing entry found in the table => VLID = %u and CO-RNTI1 = %u CO-RNTI2 = %u\n",Mod_id,eNB_index,vlid,forwardingTable->array[i].cornti1,forwardingTable->array[i].cornti2);
      
    }//end if (current_vlid == vlid)
    
    i++;
  }//end while ((i<MAX_FW_ENTRY) || (current_vlid != vlid))
  
  /* There's no existing entry, we shall create a new one */
  if (existing_entry == 0) {
    /* There's some room left in the forwarding table */
    if (forwardingTable->count < MAX_FW_ENTRY) {
      forwardingTable->array[forwardingTable->count].vlid = vlid;
      forwardingTable->array[forwardingTable->count].cornti1 = cornti;
      forwardingTable->array[forwardingTable->count].cornti2 = 0; // error value
      LOG_I(MAC,"[CONFIG][UE %d][TCS DEBUG] Configuring MAC forwarding table from eNB %d, creating a new entry in the table => VLID = %u and CO-RNTI1 = %u CO-RNTI2 = %u\n",Mod_id,eNB_index,forwardingTable->array[forwardingTable->count].vlid,forwardingTable->array[forwardingTable->count].cornti1, forwardingTable->array[forwardingTable->count].cornti2);
      forwardingTable->count++;
    }
    /* The forwarding table is full */
    else {
      ret = -1;
    }
    
  }// end if (existing_entry == 0)
  
  return ret;
}

//TCS LOLAmesh
/* Remove an entry in the forwarding table
 * return 0 = entry removed / -1 = error */
int mac_forwarding_remove_entry(u8 vlid) {
  
  return 0;
  
}

//TCS LOLAmesh
/* Get the output CORNTI associated to an input CORNTI
 * returns output CORNTI*/
int mac_forwarding_get_output_CORNTI(u8 Mod_id,
				     u8 eNB_index,
				     u8 vlid,
				     u16 cornti) {
  
  u8 current_vlid = 0;
  int i = 0;
  int output_cornti = -1;
  
  /* We look for an existing entry */
  while ((i<forwardingTable->count) && (current_vlid != vlid)) {
    
    current_vlid = forwardingTable->array[i].vlid;
    
    /* We've found it */
    if (current_vlid == vlid) {
      
      /* We fill the cornti which has an error value */
      if (forwardingTable->array[i].cornti1 == cornti) {
	output_cornti = forwardingTable->array[i].cornti2;
      }
      
      if (forwardingTable->array[i].cornti2 == cornti) {
	output_cornti = forwardingTable->array[i].cornti1;
      }
      
    }//end if (current_vlid == vlid)
    
    i++;
  }//end while ((i<MAX_FW_ENTRY) || (current_vlid != vlid))
  
  
  /* If -1 is returned, the entry is not yet initialized completely
   * or has not been found */
  return output_cornti;
  
}