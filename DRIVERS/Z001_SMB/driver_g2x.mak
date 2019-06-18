#**************************  M a k e f i l e ********************************
#  
#         Author: ts
#  
#    Description: Makefile descriptor for Z001 SMBus Controller Module,
#                 IO mapped (ISA/G22)
#-----------------------------------------------------------------------------
#   Copyright (c) 2013-2019, MEN Mikro Elektronik GmbH
#*****************************************************************************
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

MAK_NAME=lx_z001_io
# the next line is updated during the MDIS installation
STAMPED_REVISION="13Z001-90_01_14-10-g433d92c-dirty_2019-05-30"

DEF_REVISION=MAK_REVISION=$(STAMPED_REVISION)

MAK_LIBS=

MAK_SWITCH=$(SW_PREFIX)$(DEF_REVISION) \
	$(SW_PREFIX)MAC_IO_MAPPED \
	$(SW_PREFIX)CHAM_ISA_ADDR=0xf000

MAK_INCL=$(MEN_INC_DIR)/../../NATIVE/MEN/men_chameleon.h 

MAK_INP1=z001_smb$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
