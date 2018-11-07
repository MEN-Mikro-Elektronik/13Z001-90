/*********************  P r o g r a m  -  M o d u l e **********************/
/*!
 *         \file z001_smb.h
 *      \project 16Z001 I2C Host driver for Linux
 *
 *       \author ts
 *        $Date: 2013/11/08 09:53:29 $
 *    $Revision: 1.4 $
 *
 *       \brief  internal declarations 
 *                
 */
/*
 *---------------------------------------------------------------------------
 * (c) Copyright 2005 by MEN Mikro Elektronik GmbH, Nuremberg, Germany
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
#ifndef _I2C_16Z001_H_
#define _I2C_16Z001_H_

/* not in pci_ids.h yet ? */
#define PCI_VENDOR_ID_CHAMELEON   0x1172
#define PCI_DEVICE_ID_CHAMELEON   0x4d45


/** \name register offsets */
#define SMBHSI		0x00	/**< SMbus Host Config 			*/
#define SMBHCBC		0x02	/**< Base Clock Setting 		*/
#define SMBSTS		0x04	/**< Status Register 			*/
#define SMBCMD		0x05	/**< SMB Command 				*/
#define SMBSTART	0x06	/**< Start Register, wr starts cycle 	*/
#define SMBADR		0x07	/**< SMbus Address Register		*/
#define SMBDAA		0x08	/**< SMBus Data A 				*/
#define SMBDAB		0x09	/**< SMBus Data B 				*/
#define SMBBLK		0x0A	/**< SMbus Block Register	 	*/
#define SMBHCMD		0x0B	/**< SMbus Cmd Register for Host ctrl	*/
#define SMBBYP		0x0C	/**< SMbus Bypass Register		*/


/********************************
 *     Register Settings
 *******************************/
/** \name register settings  */
#define SMBCLK_149KHZ				(0x0<<5) /**< I2C clk 149kHz */
#define SMBCLK_74KHZ				(0x1<<5) /**< I2C clk  74kHz */
#define SMBCLK_37KHZ				(0x2<<5) /**< I2C clk  37kHz */
#define SMBCLK_223KHZ				(0x4<<5) /**< I2C clk 223kHz */
#define SMBCLK_111KHZ				(0x5<<5) /**< I2C clk 111kHz */
#define SMBCLK_55KHZ				(0x6<<5) /**< I2C clk  55kHz */

#define SMBHCBC_IDLE_BASECLK64		(0x0<<3) /**< IDLE delay BaseClk*64  */
#define SMBHCBC_IDLE_BASECLK32		(0x1<<3) /**< IDLE delay BaseClk*32  */
#define SMBHCBC_IDLE_BASECLK128		(0x2<<3) /**< IDLE delay BaseClk*128 */

/* FPGA16Z001 command constants */
#define FPGA16Z001_CMD_ABORT      	0x04		/**< ABORT transaction */
#define FPGA16Z001_CMD_TOUT       	0x08		/**< force TIMEOUT  */
#define FPGA16Z001_CMD_QUICK      	0x0			/**< QUICK timing */
#define FPGA16Z001_CMD_BYTE       	(0x1 << 4)  /**< Send/Receive Byte */
#define FPGA16Z001_CMD_BYTE_DATA  	(0x2 << 4)	/**< Read/Write Byte */
#define FPGA16Z001_CMD_WORD_DATA  	(0x3 << 4)	/**< Read/Write Word */
#define FPGA16Z001_CMD_BLOCK_DATA 	(0x4 << 4)	/**< Read/Write Block */
#define FPGA16Z001_CMD_BLOCK_CLR  	(0x1 << 7)	/**< Reset block registers pointer */

/* FPGA16Z001 status register bits */
#define FPGA16Z001_STS_IDLE		0x04	/**< IDL_STS */
                                        /*!< 1: Bus is idle \n
										 *   0: Bus is free */          
#define FPGA16Z001_STS_BUSY		0x08	/**< HST_BSY */
                                        /*!< 1: Host controller is completing
										 *      a command \n
										 *   0: Bus is ready */          
#define FPGA16Z001_STS_DONE		0x10	/**< Interrupt status */
                                        /*!< 1: The host controller's interrupt was 
										 *      caused after completing a command */
#define FPGA16Z001_STS_DEV		0x20	/**< Error status */
                                        /*!< 1: The host controller's interrupt was 
										 *      caused by the controller or the device
										 *      due to the generation of an error */
#define FPGA16Z001_STS_COLL		0x40	/**< Bus Collision */
                                        /*!< 1: The host controller's interrupt was 
										 *      caused by the collision of bus
										 *      transactions or no acknowledge */
#define FPGA16Z001_STS_TERM		0x80	/**< Terminate */
                                        /*!< 1: The host controller's interrupt was 
										 *      caused by a terminated bus transaction
										 *      in response to "ABORT" */
#define FPGA16Z001_STS_ERR		0xE0	/**< all error bits */

/* Host Interface Configuration Bits */
#define FPGA16Z001_HSI_HCIE		0x01	/**< Host Controller Interface Enable */ 
#define FPGA16Z001_HSI_IE		0x04	/**< Interrupt Enable */

/* Other settings */
#define MAX_TIMEOUT 				300		/* times 1/100 sec for sleep*/
#define FPGA16Z001_SMB_IOSIZE 		32

#endif  /* _I2C_16Z001_H_ */


