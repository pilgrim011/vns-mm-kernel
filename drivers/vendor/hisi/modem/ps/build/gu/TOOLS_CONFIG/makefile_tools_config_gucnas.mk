#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_gucnas

#***********************************************************#
# compiler flags
#***********************************************************#
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

#***********************************************************#
# compiler defines
#***********************************************************#
CC_USER_DEFINES ?=
AS_USER_DEFINES ?=

#***********************************************************#
# include Directories
#***********************************************************#
#ע����������ӱ����ͷ�ļ�
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/ps/gups \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/ps/tlps \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma \
	$(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
	$(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/nas/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/NASDYNLOAD/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/mntn/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/timer/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/ccb/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/SDC/Inc 


#***********************************************************#
# source files
#***********************************************************#
#ע�������������Ҫ�����Դ�ļ�
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/hids_elf_gucnas.c

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#ע���ڴ������Ҫ���õı���ű�
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
