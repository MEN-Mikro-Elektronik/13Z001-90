#**************************  M a k e f i l e ********************************
#  
#         Author: ts
#          $Date: 2013/09/25 16:18:46 $
#      $Revision: 1.1 $
#  
#    Description: Makefile descriptor for Z001 SMBus Controller Module,
#                 IO mapped (ISA/G22)
#---------------------------------[ History ]---------------------------------
#
#  $Log: driver_g2x.mak,v $
#  Revision 1.1  2013/09/25 16:18:46  ts
#  Initial Revision
#
#
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2013 by MEN mikro elektronik GmbH, Nuremberg, Germany 
#*****************************************************************************

MAK_NAME=lx_z001_io

MAK_LIBS=

MAK_SWITCH = $(SW_PREFIX)MAC_IO_MAPPED \
	 $(SW_PREFIX)CHAM_ISA_ADDR=0xf000 \


MAK_INCL=$(MEN_INC_DIR)/../../NATIVE/MEN/men_chameleon.h 

MAK_INP1=z001_smb$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
