include $(OPENAIR_HOME)/common/utils/Makefile.inc

TOP_DIR = $(OPENAIR1_DIR)
OPENAIR1_TOP = $(OPENAIR1_DIR)
OPENAIR2_TOP = $(OPENAIR2_DIR)
OPENAIR3 = $(OPENAIR3_DIR)

CFLAGS +=  -DPHYSIM -DNODE_RG -DUSER_MODE -DPC_TARGET -DPC_DSP -DNB_ANTENNAS_RX=2 -DNB_ANTENNAS_TXRX=2 -DNB_ANTENNAS_TX=2 -DPHY_CONTEXT=1 # -Wno-packed-bitfield-compat

LFLAGS = -lm -lblas -lrt

CFLAGS += -m32 -DOPENAIR_LTE -DOFDMA_ULSCH #-DIFFT_FPGA -DIFFT_FPGA_UE
#CFLAGS += -DTBS_FIX
CFLAGS += -DCELLULAR

ASN1_MSG_INC = $(OPENAIR2_DIR)/RRC/LITE/MESSAGES

ifdef EMOS
CFLAGS += -DEMOS
endif

ifdef DEBUG_PHY
CFLAGS += -DDEBUG_PHY
endif

ifdef MeNBMUE
CFLAGS += -DMeNBMUE
endif

ifdef MU_RECEIVER
CFLAGS += -DMU_RECEIVER
endif

ifdef ZBF_ENABLED
CFLAGS += -DNULL_SHAPE_BF_ENABLED
endif

ifdef RANDOM_BF
CFLAGS += -DRANDOM_BF
endif

ifdef PBS_SIM
CFLAGS += -DPBS_SIM
endif

ifdef XFORMS
CFLAGS += -DXFORMS
LFLAGS += -lforms
endif

ifdef PERFECT_CE
CFLAGS += -DPERFECT_CE
endif

CFLAGS += -DNO_RRM -DOPENAIR2 #-DPHY_ABSTRACTION

CFLAGS += -I/usr/include/X11 -I/usr/X11R6/include


all: colabsim

include $(TOP_DIR)/PHY/Makefile.inc
#SCHED_OBJS = $(TOP_DIR)/SCHED/phy_procedures_lte_common.o $(TOP_DIR)/SCHED/phy_procedures_lte_eNb.o $(TOP_DIR)/SCHED/phy_procedures_lte_ue.o
include $(TOP_DIR)/SCHED/Makefile.inc
include $(TOP_DIR)/SIMULATION/Makefile.inc
include $(OPENAIR2_DIR)/LAYER2/Makefile.inc
include $(OPENAIR2_DIR)/UTIL/Makefile.inc
include $(OPENAIR2_DIR)/RRC/LITE/MESSAGES/Makefile.inc

CFLAGS += $(L2_incl) -I$(ASN1_MSG_INC) -I$(TOP_DIR) -I$(OPENAIR3) ${UTIL_incl}
#EXTRA_CFLAGS = 

#STATS_OBJS += $(TOP_DIR)/ARCH/CBMIMO1/DEVICE_DRIVER/cbmimo1_proc.o

#LAYER2_OBJ += $(OPENAIR2_DIR)/LAYER2/MAC/rar_tools.o
LAYER2_OBJ = $(OPENAIR2_DIR)/LAYER2/MAC/lte_transport_init.o

OBJ = $(PHY_OBJS) $(SIMULATION_OBJS) $(TOOLS_OBJS) $(SCHED_OBJS) $(LAYER2_OBJ) $(LOG_OBJS) #$(ASN1_MSG_OBJS) 

ifdef XFORMS
OBJ += ../../USERSPACE_TOOLS/SCOPE/lte_scope.o
endif

$(OBJ) : %.o : %.c
	@echo 
	@echo Compiling $< ...
	@$(CC) -c $(CFLAGS) -o $@ $<

colabsim : $(OBJ) colabsim.c
	@echo "Compiling colabsim.c ..."
	@$(CC) colabsim.c  -o colabsim $(CFLAGS) $(OBJ) $(LFLAGS) #-static -L/usr/lib/libblas

clean :
	rm -f $(OBJ)
	rm -f *.o

cleanall : clean
	rm -f colabsim
	rm -f *.exe*

showcflags :
	@echo $(CFLAGS)

