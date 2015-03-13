#**************************  M a k e f i l e ********************************
#  
#         Author: ts
#          $Date: 2007/03/05 16:18:19 $
#      $Revision: 1.1 $
#  
#    Description: makefile descriptor for Z001 SMBus Controller Module
#                      
#---------------------------------[ History ]---------------------------------
#
#  $Log: driver.mak,v $
#  Revision 1.1  2007/03/05 16:18:19  ts
#  Initial Revision
#
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2007 by MEN mikro elektronik GmbH, Nuremberg, Germany 
#*****************************************************************************

MAK_NAME=lx_z001

MAK_LIBS=

MAK_SWITCH = -DEXPORT_SYMTAB -DMAC_MEM_MAPPED

MAK_INCL=$(MEN_INC_DIR)/../../NATIVE/MEN/men_chameleon.h 

MAK_INP1=z001_smb$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
