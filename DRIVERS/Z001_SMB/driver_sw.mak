#**************************  M a k e f i l e ********************************
#  
#         Author: ts
#          $Date: 2007/03/27 20:05:43 $
#      $Revision: 1.1 $
#  
#    Description: makefile descriptor for Z001 SMBus Controller Module,
#                 byteswapped access
#---------------------------------[ History ]---------------------------------
#
#  $Log: driver_sw.mak,v $
#  Revision 1.1  2007/03/27 20:05:43  ts
#  Initial Revision
#
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2007 by MEN mikro elektronik GmbH, Nuremberg, Germany 
#*****************************************************************************

MAK_NAME=lx_z001_sw

MAK_LIBS=

MAK_SWITCH=$(SW_PREFIX)MAC_MEM_MAPPED \
		   $(SW_PREFIX)MAC_BYTESWAP   \
		   $(SW_PREFIX)EXPORT_SYMTAB


MAK_INCL=$(MEN_INC_DIR)/../../NATIVE/MEN/men_chameleon.h 

MAK_INP1=z001_smb$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
