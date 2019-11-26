/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  z001_smb_doc.c
 *
 *      \author  Christian.Schuster@men.de
 *
 *      \brief   User documentation for MEN 16Z001 I2C host driver for Linux
 *
 *     Required: -
 *
 *     \switches -
 */
/*
 *---------------------------------------------------------------------------
 * Copyright 2013-2019, MEN Mikro Elektronik GmbH
 ****************************************************************************/
/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*! \mainpage
  This is the documentation of the Linux low-level driver for the
  MEN 16Z001 I2C host.

  \section General
  The 16Z001 is an I2C/SMB host controller compatible to the ALI 15x3 I2C
  module. It supports the following SMB clock frequencies:

  - 37 kHz
  - 55 kHz
  -	74 kHz
  -	111 kHz
  - 149 kHz
  - 223 kHz
\n

  The default frequency used when smbClk is not passed is 74 kHz. A frequency value is passed
  in [kHz] unit during the modprobe call:
\verbatim
    #/modprobe men_lx_z001 smbClk=37    for 37 kHz or
    #/modprobe men_lx_z001 smbClk=111   for 111 kHz
\endverbatim

  

  \section 

  The driver consists of the following files:
  z001_smb.c				Adapter driver, similar to i2c-ali15x3\n
  z001_smb.h				Header file for driver\n
  driver.mak				Makefile part for building Driver as Part of MDIS
  z001_smb_doc.c			Source for software documentation
  Makefile				MDIS demo Makefile 

  \section build_install Build/Install

  The Driver is primarily built in conjunction with the Linux MDIS
  package. The resulting kernel module men_lx_z001(_io) depends on Functions
  in the men_oss and men_chameleon modules.
	
  Therefore the most recent Linux MDIS5 Package 13MD05-90 from MEN Website
  is needed to build the driver.

  \section test Usage / Test example
  The following example/test was performed to verify the functionality
  of the driver:

  CPU board: 02F014-00
  Target: 02F210 GPS/GSM Module with Onboard FPGA
	       
  \verbatim

  The utilities i2cdetect and i2cdump are used to verify the showup of
  the additional 2 SMBus devices when the Driver is loaded.

  The Linux Kernelmodule of the 16Z001 driver is loaded via 
  modprobe men_lx_z001

  -sh-3.00# i2cdetect
  Error: No i2c-bus specified!
  Syntax: i2cdetect [-y] [-a] [-q|-r] I2CBUS [FIRST LAST]
  i2cdetect -l
  i2cdetect -V
  I2CBUS is an integer
  With -a, probe all addresses (NOT RECOMMENDED)
  With -q, uses only quick write commands for probing (NOT RECOMMENDED)
  With -r, uses only read byte commands for probing (NOT RECOMMENDED)
  If provided, FIRST and LAST limit the probing range.
  With -l, lists installed busses only
  Installed I2C busses:
  i2c-0       unknown     SMBus I801 adapter at 0500  Algorithm unavailable


  -sh-3.00# modprobe men_lx_z001
  -sh-3.00# i2cdetect
  Error: No i2c-bus specified!
  Syntax: i2cdetect [-y] [-a] [-q|-r] I2CBUS [FIRST LAST]
  i2cdetect -l
  i2cdetect -V
  I2CBUS is an integer
  With -a, probe all addresses (NOT RECOMMENDED)
  With -q, uses only quick write commands for probing (NOT RECOMMENDED)
  With -r, uses only read byte commands for probing (NOT RECOMMENDED)
  If provided, FIRST and LAST limit the probing range.
  With -l, lists installed busses only
  Installed I2C busses:
  i2c-2  unknown    16Z001-1 BAR0 offs 0x600      Algorithm unavailable
  i2c-1  unknown    16Z001-0 BAR0 offs 0x500      Algorithm unavailable
  i2c-0  unknown    SMBus I801 adapter at 0500    Algorithm unavailable
  -sh-3.00#

  \endverbatim

  \section g22 CPU Board: MEN G22

  On the G22 the compact serial IO connector carries the I2C signals of the
  16Z001 controller located at address 0xf000 in the ISA IO space. A special
  driver mak file driver_g2x.mak is used to build a IO mapped version of the 
  driver. \n
  On G22 there are alot I2C busses present due to the i915 chipset driver that
  implements many busses via bitbang algorithms to read DDC and EDID data from
  monitors. \n
  The following dump shows the I2C devices present on a G22 under Ubuntu 12.04,
  then the load of the driver module followed by accessing a Test cPCI serial
  adapter. There an I2C EEPROM at address 0x51 is located.


  \verbatim
  root@MENVPC:~# 
  root@MENVPC:~# l /dev/i2c-*
  crw-rw---- 1 root i2c 89,  0 Sep 25 15:47 /dev/i2c-0
  crw-rw---- 1 root i2c 89,  1 Sep 25 15:47 /dev/i2c-1
  crw-rw---- 1 root i2c 89, 10 Sep 25 15:47 /dev/i2c-10
  crw-rw---- 1 root i2c 89, 11 Sep 25 15:47 /dev/i2c-11
  crw-rw---- 1 root i2c 89, 12 Sep 25 15:47 /dev/i2c-12
  crw-rw---- 1 root i2c 89, 13 Sep 25 15:47 /dev/i2c-13
  crw-rw---- 1 root i2c 89, 14 Sep 25 15:47 /dev/i2c-14
  crw-rw---- 1 root i2c 89, 15 Sep 25 15:47 /dev/i2c-15
  crw-rw---- 1 root i2c 89,  2 Sep 25 15:47 /dev/i2c-2
  crw-rw---- 1 root i2c 89,  3 Sep 25 15:47 /dev/i2c-3
  crw-rw---- 1 root i2c 89,  4 Sep 25 15:47 /dev/i2c-4
  crw-rw---- 1 root i2c 89,  5 Sep 25 15:47 /dev/i2c-5
  crw-rw---- 1 root i2c 89,  6 Sep 25 15:47 /dev/i2c-6
  crw-rw---- 1 root i2c 89,  7 Sep 25 15:47 /dev/i2c-7
  crw-rw---- 1 root i2c 89,  8 Sep 25 15:47 /dev/i2c-8
  crw-rw---- 1 root i2c 89,  9 Sep 25 15:47 /dev/i2c-9
  root@MENVPC:~# 
  root@MENVPC:~# 
  root@MENVPC:~# modprobe men_lx_z001_io
  root@MENVPC:~# l /dev/i2c-*
  crw-rw---- 1 root i2c 89,  0 Sep 25 15:47 /dev/i2c-0
  crw-rw---- 1 root i2c 89,  1 Sep 25 15:47 /dev/i2c-1
  crw-rw---- 1 root i2c 89, 10 Sep 25 15:47 /dev/i2c-10
  crw-rw---- 1 root i2c 89, 11 Sep 25 15:47 /dev/i2c-11
  crw-rw---- 1 root i2c 89, 12 Sep 25 15:47 /dev/i2c-12
  crw-rw---- 1 root i2c 89, 13 Sep 25 15:47 /dev/i2c-13
  crw-rw---- 1 root i2c 89, 14 Sep 25 15:47 /dev/i2c-14
  crw-rw---- 1 root i2c 89, 15 Sep 25 15:47 /dev/i2c-15
  crw-rw---- 1 root i2c 89, 16 Sep 25 16:15 /dev/i2c-16
  crw-rw---- 1 root i2c 89,  2 Sep 25 15:47 /dev/i2c-2
  crw-rw---- 1 root i2c 89,  3 Sep 25 15:47 /dev/i2c-3
  crw-rw---- 1 root i2c 89,  4 Sep 25 15:47 /dev/i2c-4
  crw-rw---- 1 root i2c 89,  5 Sep 25 15:47 /dev/i2c-5
  crw-rw---- 1 root i2c 89,  6 Sep 25 15:47 /dev/i2c-6
  crw-rw---- 1 root i2c 89,  7 Sep 25 15:47 /dev/i2c-7
  crw-rw---- 1 root i2c 89,  8 Sep 25 15:47 /dev/i2c-8
  crw-rw---- 1 root i2c 89,  9 Sep 25 15:47 /dev/i2c-9
  root@MENVPC:~# 
  root@MENVPC:~# i2cdetect -y 16
  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
  00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
  10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  50: -- 51 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
  70: -- -- -- -- -- -- -- --                         
  root@MENVPC:~# i2cdump -y 16 0x51
  No size specified (using byte-data access)
  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef
  00: 41 42 43 ff ff ff ff ff ff ff ff ff ff ff ff ff    ABC.............
  10: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  20: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  30: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  40: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  50: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  60: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  70: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  80: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  90: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  a0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  b0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  c0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  d0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  e0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  f0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
  root@MENVPC:~# 
  root@MENVPC:~# 
  root@MENVPC:~# i2cdetect -l
  i2c-0   i2c             i915 gmbus disabled                     I2C adapter
  i2c-1   i2c             i915 gmbus ssc                          I2C adapter
  i2c-2   i2c             i915 GPIOB                              I2C adapter
  i2c-3   i2c             i915 gmbus vga                          I2C adapter
  i2c-4   i2c             i915 GPIOA                              I2C adapter
  i2c-5   i2c             i915 gmbus panel                        I2C adapter
  i2c-6   i2c             i915 GPIOC                              I2C adapter
  i2c-7   i2c             i915 gmbus dpc                          I2C adapter
  i2c-8   i2c             i915 GPIOD                              I2C adapter
  i2c-9   i2c             i915 gmbus dpb                          I2C adapter
  i2c-10  i2c             i915 GPIOE                              I2C adapter
  i2c-11  i2c             i915 gmbus reserved                     I2C adapter
  i2c-12  i2c             i915 gmbus dpd                          I2C adapter
  i2c-13  i2c             i915 GPIOF                              I2C adapter
  i2c-14  i2c             DPDDC-C                                 I2C adapter
  i2c-15  i2c             DPDDC-D                                 I2C adapter
  i2c-16  smbus           16Z001-0-0xf000                         SMBus adapter
  root@MENVPC:~# 
  root@MENVPC:~# 
  \endverbatim


*/

/** \page z001dummy MEN logo
	\menimages
*/
