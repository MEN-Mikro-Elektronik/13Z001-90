/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  z001_smb.c
 *
 *      \author  ts
 *
 *        \brief Register a Z001 SMB Controller unit at the i2c 
 *				 core subsystem
 *
 */
/*
 *---------------------------------------------------------------------------
 * Copyright (c) 2007-2019, MEN Mikro Elektronik GmbH
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

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>

#include <MEN/men_chameleon.h>
#include <MEN/men_typs.h>
#include <MEN/maccess.h>
#include <MEN/16z001_smb.h>

/* set to define if debugprints desired  */
#undef Z001DBG

#ifdef Z001DBG
#define DBGOUT(x...) printk(KERN_CRIT x)
#else
#define DBGOUT(x...)
#endif /* DBG */

#define ADDSHIFT(addr) ((addr & 0x7f) << 1)
#define MAX_TIMEOUT 	100	/* times 1/100 sec for sleep*/
#define SMB_CLK_37K     37      
#define SMB_CLK_55K     55
#define SMB_CLK_74K     74
#define SMB_CLK_111K    111
#define SMB_CLK_149K    149
#define SMB_CLK_223K    223

/* passed by corresponding mak file */
#ifndef CHAM_ISA_ADDR
#define CHAM_ISA_ADDR   0
#endif

/*-----------------------------------------+
|  TYPEDEFS                                |
+-----------------------------------------*/

/** structure with private data stored as driver_data in chameleon_unit */
typedef struct {
    struct list_head 	node;		/* linked list maintenance 	*/
	unsigned long 	physBase;	/* from chu->base 			*/
        unsigned long   ioBase;	        /* ioremapped virt Base for MWRITE/MREAD */
	struct i2c_adapter 	adapter;
} Z001_DRVDATA_T;


/*-----------------------------------------+
|  PROTOTYPES                              |
+-----------------------------------------*/

static Z001_DRVDATA_T *getDriverData(struct i2c_adapter *adap );
static s32 z001_access(struct i2c_adapter *adap,u16 addr, unsigned short flags,
					   char read_write, u8 command, int size, union i2c_smbus_data *data);
static u32 z001_func(struct i2c_adapter *adapter);
static void men16z001_pause( unsigned int amount );



/*-----------------------------------------+
|  GLOBALS							       |
+-----------------------------------------*/

#ifndef MAC_IO_MAPPED
static u16 G_modCodeArr[] = {	CHAMELEON_16Z001_SMB, 
								CHAMELEON_MODCODE_END };
#endif

static struct list_head	G_z001ListHead;

static Z001_DRVDATA_T *G_z001drvDataP=NULL;

/* 
 * module parameters 
 */
static uint smbClk = SMB_CLK_74K;	 		/* SMBus clock, use default=74 kHz */
static uint isa_addr = CHAM_ISA_ADDR;		/* for IO mapped build: ISA address to use */

module_param(smbClk, uint, 0664 );
module_param(isa_addr, uint, 0664 );
MODULE_PARM_DESC(isa_addr,"ISA address (only IO mapped SMB controller)");
MODULE_PARM_DESC(smbClk, "smbClk [kHz]: 37, 55, 74, 111, 149, 223 default: 74");

static int G_instance=0;

/**************************** men16z001_pause *******************************/
/** Let driver sleep while waiting for an I2C transaction to finish
 *
 *  \param amount	\IN sleep time in ticks
 *  \return         \c -
 *
 *  \brief  Puts driver to sleep since SMBus transactions are not 
 *			only slow in general, but also because a SMBus slave can 
 *			delay a transaction by a quiet long time
 */
static void men16z001_pause( unsigned int amount )
{
	current->state = TASK_INTERRUPTIBLE;
	schedule_timeout(amount);
}




/****************************************************************************/
/** central HW access function for all SMBus transfers
 *
 *  \param adap      	\IN  The I2C Adapter that was registered during probe
 *  \param addr      	\IN  The SMBus address
 *  \param flags      	\IN  special Flags for transfer
 *  \param read_write 	\IN  transfer direction: 1 = read
 *  \param command     	\IN  
 *  \param size	    	\IN  
 *  \param data     	\IN  
 *
 *  \return          \c   0 if transfer ok or error code
 */
static s32 z001_access(struct i2c_adapter *adap, 
					   u16 addr,
					   unsigned short flags, 
					   char read_write, 
					   u8 command,
					   int size, 	
					   union i2c_smbus_data *data)
{
	int i,len;
	int temp;
	Z001_DRVDATA_T  *drvData = NULL;
	unsigned int timeout = 0;
	char statusReg = 0;
	int error = 0;
	unsigned long ioaddr;
			
	drvData = getDriverData(adap);
	ioaddr = drvData->ioBase;

	if (!ioaddr) {
		printk(KERN_ERR "*** z001_access: Adapter %08x not found!", adap);
		return -ENODEV;
	}

    
    if (statusReg & Z001_SMB_STS_ERR)
    {
        error = -EIO;
        /* clear error Status Bits */
	MWRITE_D8(ioaddr, Z001_SMB_STS, Z001_SMB_STS_ERR );
	    
	    goto exit;
    }
    
	/* clear error Status Bits */
	MWRITE_D8(ioaddr, Z001_SMB_STS, Z001_SMB_STS_ERR );

	/* make sure SMBus is idle */
	do {
		temp = MREAD_D8(ioaddr, Z001_SMB_STS );

		if( temp & Z001_SMB_STS_IDLE ) {
			break;
		} else {
			men16z001_pause(1);
			timeout++;
		}
		/* while no timeout and SMBus NOT idle (bit IDL_STS=1 means IDLE */
	} while (timeout < MAX_TIMEOUT); 
	
	if (timeout >= MAX_TIMEOUT) {
		printk("z001_smb: Idle wait Timeout! STS=0x%02x\n", temp); 
		
		error = -EBUSY;
		
		goto exit;
	}
    
	DBGOUT("16z001_access: r/w=%d command=%d addr=0x%02x size=%d\n",
			read_write, command, ADDSHIFT(addr), size);

    /* --- write address and commands --- */

	switch(size) {
    case I2C_SMBUS_PROC_CALL:
		DBGOUT("I2C_SMBUS_PROC_CALL (unsupported)\n");
		break;

    case I2C_SMBUS_QUICK:
		DBGOUT("I2C_SMBUS_QUICK\n");
		MWRITE_D8(ioaddr, Z001_SMB_ADDR, ADDSHIFT(addr)|(read_write & 1));
		MWRITE_D8(ioaddr, Z001_SMB_CMD, Z001_SMB_CMD_QUICK);		
		size = Z001_SMB_CMD_QUICK;
		break;

    case I2C_SMBUS_BYTE:
		DBGOUT("I2C_SMBUS_BYTE\n");
		MWRITE_D8(ioaddr, Z001_SMB_ADDR, ADDSHIFT(addr)|(read_write & 1));
		MWRITE_D8(ioaddr, Z001_SMB_CMD, Z001_SMB_CMD_BYTE);		

		if ( read_write == I2C_SMBUS_WRITE )
		{
		  MWRITE_D8(ioaddr, Z001_SMB_HSTCOM, command);
		}
	
        size = Z001_SMB_CMD_BYTE;
		break;

    case I2C_SMBUS_BYTE_DATA:
		DBGOUT("I2C_SMBUS_BYTE_DATA\n");

		/* SMB_address from which we read/write */
		MWRITE_D8(ioaddr, Z001_SMB_ADDR, ADDSHIFT(addr)|(read_write & 1));

		/* The command is: read/write byte */
		MWRITE_D8(ioaddr, Z001_SMB_CMD, Z001_SMB_CMD_BYTE_DATA );

		/* Parameter command contains the actual address in the device */
		MWRITE_D8(ioaddr, Z001_SMB_HSTCOM, command );

		if (read_write == I2C_SMBUS_WRITE)
			MWRITE_D8(ioaddr, Z001_SMB_DATA_A, data->byte );

		size = Z001_SMB_CMD_BYTE_DATA;
		break;


    case I2C_SMBUS_WORD_DATA:
	    DBGOUT("I2C_SMBUS_WORD_DATA\n");

		/* SMB address of the device */
		MWRITE_D8(ioaddr, Z001_SMB_ADDR, ADDSHIFT(addr)|(read_write&1));

		/* The command is: read/write word */
		MWRITE_D8(ioaddr, Z001_SMB_CMD, Z001_SMB_CMD_WORD_DATA);

		/* Parameter command contains the actual address in the device */
		MWRITE_D8(ioaddr, Z001_SMB_HSTCOM, command);

		/* If we do writing, provide the word in DataA and DataB.
		   N.B.: Refer to Devices Manual for byte order!*/
		if (read_write == I2C_SMBUS_WRITE) {
			MWRITE_D8(ioaddr, Z001_SMB_DATA_A,	data->word & 0xff		);
			MWRITE_D8(ioaddr, Z001_SMB_DATA_B,	(data->word & 0xff00) >> 8 	);
		}

		size = Z001_SMB_CMD_WORD_DATA;
		break;


    case I2C_SMBUS_BLOCK_DATA:
		DBGOUT("I2C_SMBUS_BLOCK_DATA\n");

		/* SMB address of the device */
		MWRITE_D8(ioaddr, Z001_SMB_ADDR, ADDSHIFT(addr) | (read_write & 1));

		/* The command is: read/write block */
		MWRITE_D8(ioaddr, Z001_SMB_CMD, Z001_SMB_CMD_BLOCK_DATA);

		/* Actual address we want to make the block transfer to & from */
		MWRITE_D8(ioaddr, Z001_SMB_HSTCOM, command);

		if (read_write == I2C_SMBUS_WRITE) {
			len = data->block[0];
			if (len < 0) {
				len = 0;
				data->block[0] = len;
			}	
			if (len > 32) {
				len = 32;
				data->block[0] = len;
			}	

			/* Data Register A contains length of transfer */
			MWRITE_D8(ioaddr, Z001_SMB_DATA_A, len);

			/* Clear Block Register & set command to read/write block */
			MWRITE_D8(ioaddr, Z001_SMB_CMD, 
					  Z001_SMB_CMD_BLOCK_DATA | Z001_SMB_CMD_BLOCK_CLR);

			/* Write up to 32 bytes to block Data Register */
			for (i = 1; i <= len; i++)
				MWRITE_D8(ioaddr, Z001_SMB_BLK, data->block[i]);
		}

		size = Z001_SMB_CMD_BLOCK_DATA;
		break;
	}
    
	/* Kick off the actual transaction by writing to Z001_SMB_START_PRT */
	MWRITE_D8(ioaddr, Z001_SMB_START_PRT, 0x01);

	/* Now wait till cycle completed */
	do {
		men16z001_pause(1);
		temp = MREAD_D8(ioaddr, Z001_SMB_STS);
		timeout++;
		/* Pause while SMBus is busy (bit Z001_SMB_STS_BUSY = 1 means busy */
	} 	while ((timeout < MAX_TIMEOUT) && (temp & Z001_SMB_STS_BUSY));

	/* If the SMBus is still busy, we complain */
	if ( timeout >= MAX_TIMEOUT) {
		printk(KERN_ERR "*** SMBus transaction Timeout! STS=0x%02x\n", temp); 
	    
	    error = -EBUSY;
	    goto exit;
	}

	/* If we made a write or quick access we are finished */
	if ((read_write == I2C_SMBUS_WRITE) || (size == Z001_SMB_CMD_QUICK))
	{
	  /* check also if we got an ACK or ghost devices are present when using i2cdetect */
	  if (MREAD_D8(ioaddr, Z001_SMB_STS) & Z001_SMB_STS_ERR) {
	    error = -EIO;
	  } else {
	    error = 0;
	  }
	  goto exit;
	}
  
	/* --- If we made a read, read data according to command type ----*/
	switch(size) {

    case Z001_SMB_CMD_BYTE: /* Result put in SMBHSTDAT0 */
		data->byte = MREAD_D8(ioaddr, Z001_SMB_DATA_A);
		break;

    case Z001_SMB_CMD_BYTE_DATA:
		data->byte = MREAD_D8(ioaddr, Z001_SMB_DATA_A);
		DBGOUT("read: 0x%02x\n", data->byte);
		break;

    case Z001_SMB_CMD_WORD_DATA:
		data->word = MREAD_D8(ioaddr,Z001_SMB_DATA_A) + (MREAD_D8(ioaddr, Z001_SMB_DATA_B) << 8);
		break;
		
    case Z001_SMB_CMD_BLOCK_DATA:
		/* Number of bytes for block transfer */
		len = MREAD_D8(ioaddr, Z001_SMB_DATA_A);
		if(len > 32)	
			len = 32;
		data->block[0] = len;

		/* Clear Block Register & set command to read/write block */
		MWRITE_D8(ioaddr, Z001_SMB_CMD, 
				  Z001_SMB_CMD_BLOCK_DATA | Z001_SMB_CMD_BLOCK_CLR);

		for (i = 1; i <= data->block[0]; i++) {
			data->block[i] = MREAD_D8(ioaddr, Z001_SMB_BLK);
		}
		break;
	}
	
	/* Check if error occured */
    statusReg = MREAD_D8(ioaddr, Z001_SMB_STS);
    DBGOUT( "z001_access: statusReg = %02x\n", statusReg);
    
    if (statusReg & Z001_SMB_STS_ERR)
    {
        error = -EIO;
        DBGOUT( "*** z001_access: SMB error occured, STS Reg.: 0x%x!", statusReg);
        
        /* clear error Status Bits */
	    MWRITE_D8(ioaddr, Z001_SMB_STS, Z001_SMB_STS_ERR );	    
	    goto exit;
    }
	
exit:
    return error;
}


/****************************************************************************/
/** Retrieve this Adapters supported functions
 *
 *  \param adapter   \IN  The I2C Adapter that was registered during probe
 *
 *  \return          \c   Flags with supported functionality
 */
static u32 z001_func(struct i2c_adapter *adapter)
{
	/* return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA ; */

	return (I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_WRITE_I2C_BLOCK | I2C_FUNC_SMBUS_READ_I2C_BLOCK);
}


/****************************************************************************/
/** SMBuss access algorithm function struce
 *
 */
static struct i2c_algorithm smbus_algorithm = {
	.smbus_xfer		= z001_access,
	.functionality	= z001_func,
};



/****************************************************************************/
/** Retrieve the private driver data of this Adapter
 *
 *  \param adap      \IN  The I2C Adapter that was registered during probe
 *
 *  \return          \c   Z001_DRVDATA_T entry for this Z001 instancess
 */
static Z001_DRVDATA_T *getDriverData(struct i2c_adapter *adap )
{

    struct list_head  	*pos 	= NULL;
    Z001_DRVDATA_T		*ent 	= NULL;
    list_for_each( pos, &G_z001ListHead ) {
		ent = list_entry( pos, Z001_DRVDATA_T, node );
		if (&ent->adapter == adap)
			return(ent);
    }
    printk( KERN_ERR "*** i2c_adapter 0x%08x not found!\n", adap );
    return(NULL);
}


/*******************************************************************/
/** PNP function to probe a found Z001 Unit
 *
 * This gets called when the chameleon PNP subsystem starts and
 * is called for each Z001 unit. The Function registers the i2c_adapter
 * then.
 *
 * \param chu	\IN 	z001 unit found
 *
 * \return 		0 on success or negative linux error number
 */
static int z001_probe( CHAMELEON_UNIT_T *chu )
{
	int res;
	Z001_DRVDATA_T  *drvData = NULL;
	unsigned char regVal = 0;

	if (chu != NULL ) {
		DBGOUT("z001_probe: Z001 Unit @ BAR %d offset 0x%x phys Adress.: 0x%p\n",
			   chu->bar, chu->offset, chu->phys );
	} else {
		DBGOUT("z001_probe: *chu = NULL, trying phys. ISA address 0x%x\n", isa_addr);
	}

	/*+------------------------+
	  |alloc driver data memory|
	  +------------------------*/


	drvData = kmalloc( sizeof(Z001_DRVDATA_T), GFP_KERNEL );
	memset(drvData, 0x00, sizeof(Z001_DRVDATA_T));
	if( !drvData ){
		printk( KERN_ERR "*** z001_probe: no memory!\n");
		return -ENOMEM;
	}

	/* populate i2c_adapter member, the structs members differ in 2.4/2.6 */
	drvData->adapter.owner      = THIS_MODULE;
	drvData->adapter.class      = I2C_CLASS_HWMON;
	drvData->adapter.algo       = &smbus_algorithm;
	if (chu != NULL ) {
		drvData->adapter.dev.parent = &chu->pdev->dev;
	}
	else {
		drvData->adapter.dev.parent = NULL;
	}

	if (chu != NULL ) {		

	  sprintf( drvData->adapter.name, "16Z001-%d BAR%d offs 0x%x", chu->instance, chu->bar, chu->offset);
#ifdef CONFIG_PCI
	  drvData->physBase = (unsigned long)(pci_resource_start(chu->pdev,chu->bar) + chu->offset);
#else
	  drvData->physBase = chu->offset;
#endif		
	  drvData->ioBase = (unsigned long)ioremap_nocache((unsigned long)drvData->physBase, 0x100);
		
	  DBGOUT("z001_probe: remapped 0x%08x to 0x%08x\n", drvData->physBase, drvData->ioBase );		

	} else {

	  drvData->physBase = isa_addr;
	  drvData->ioBase = drvData->physBase;
	  sprintf( drvData->adapter.name, "16Z001-%d-0x%x", G_instance++, drvData->ioBase );
	  DBGOUT("z001_probe: using ISA address 0x%08x\n", drvData->ioBase );
	}

    list_add(&drvData->node, &G_z001ListHead);

	/*+------------------------+
	  |  Init hardware         |
	  +------------------------*/

	/* setup speed (SMB clk) */

	switch (smbClk) {
	case SMB_CLK_37K:
		regVal = Z001_SMB_HCBC_BASECLK_37KHZ;
		break;
	case SMB_CLK_55K:
		regVal = Z001_SMB_HCBC_BASECLK_55KHZ;
		break;
	case SMB_CLK_74K:
		regVal = Z001_SMB_HCBC_BASECLK_74KHZ;
		break;
	case SMB_CLK_111K:
		regVal = Z001_SMB_HCBC_BASECLK_111KHZ;
		break;
	case SMB_CLK_149K:
		regVal = Z001_SMB_HCBC_BASECLK_149KHZ;
		break;
	case SMB_CLK_223K:
		regVal = Z001_SMB_HCBC_BASECLK_223KHZ;
		break;
	default:
		printk(KERN_ERR "*** invalid value %d for SMB clk speed, using default (74kHz)\n", smbClk);
		regVal = Z001_SMB_HCBC_BASECLK_74KHZ;		
	}
	
	/* Setup frequency: */
	MWRITE_D8( drvData->ioBase, Z001_SMB_HCBC, regVal | Z001_SMB_HCBC_IDLE_BASECLK32 );
		
	/* Activate and reset Host controller */
	MWRITE_D8( drvData->ioBase, Z001_SMB_HSI, Z001_SMB_HSI_HCIE );  

	/* Here actually adding the adapter happens */
	if ( (res = i2c_add_adapter(&drvData->adapter)) ) {
		printk(KERN_ERR "i2c-men16z001: Adapter reg. failed, module not inserted.\n");
		return res;
	}

	/* store the private data */
	if (chu)
		chu->driver_data = drvData;		
	else
		G_z001drvDataP = drvData;

	return 0;
}


/*******************************************************************/
/** PNP function to remove a registered Z001 SMBus adapter 
 *
 * \param chu		\IN frodo unit to remove, NULL for ISA device
 *
 * \return 0 on success or negative linux error number
 */
static int z001_remove( CHAMELEON_UNIT_T *chu )
{

	int res = 0;
	Z001_DRVDATA_T  *drvData = NULL;

	if (chu)
		drvData = chu->driver_data;		
	else
		drvData = G_z001drvDataP;

	/* remove adapter from kernel */
	i2c_del_adapter( &drvData->adapter );


	/* unmap ioremap'ed area */
	if (chu)
	  iounmap((void*)(drvData->ioBase));

	/* remove the linked list entry */
	list_del(&drvData->node);

	/* free driver data space */
	kfree(drvData);
	G_z001drvDataP = NULL;

	return res;
}


#ifndef MAC_IO_MAPPED
static CHAMELEON_DRIVER_T G_driver = {
	.name		=		"z001_smb",
	.modCodeArr     = 		G_modCodeArr,
	.probe		=		z001_probe,
	.remove		= 		z001_remove
};
#endif



/*******************************************************************/
/** module init function
 *
 */
static int __init z001_smb_init(void)
{
	printk(	KERN_INFO "MEN SMB controller driver for IP core 16Z001_SMB\n" );

    /* init linux lists and locking */
    INIT_LIST_HEAD( &G_z001ListHead );
#ifndef MAC_IO_MAPPED
    men_chameleon_register_driver( &G_driver );
#else
    z001_probe(NULL);
#endif
    return 0;
}


/*******************************************************************/
/** module exit function
 *
 */
static void __exit z001_smb_exit(void)
{
	DBGOUT("z001_smb_exit\n");
#ifndef MAC_IO_MAPPED
	men_chameleon_unregister_driver( &G_driver );
#else
	z001_remove( NULL );
#endif

}

MODULE_AUTHOR ("thomas.schnuerer@men.de");
MODULE_DESCRIPTION("MEN 16Z001 SMBus driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(MENT_XSTR(MAK_REVISION));

module_init(z001_smb_init);
module_exit(z001_smb_exit);
