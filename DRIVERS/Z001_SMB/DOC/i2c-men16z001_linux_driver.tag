<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="page">
    <filename>index</filename>
    <title></title>
    <name>index</name>
  </compound>
  <compound kind="file">
    <name>z001_smb.c</name>
    <path>/opt/menlinux/DRIVERS/Z001_SMB/</path>
    <filename>z001__smb_8c</filename>
    <class kind="struct">Z001_DRVDATA_T</class>
    <member kind="function" static="yes">
      <type>Z001_DRVDATA_T *</type>
      <name>getDriverData</name>
      <anchor>a18</anchor>
      <arglist>(struct i2c_adapter *adap)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>s32</type>
      <name>z001_access</name>
      <anchor>a19</anchor>
      <arglist>(struct i2c_adapter *adap, u16 addr, unsigned short flags, char read_write, u8 command, int size, union i2c_smbus_data *data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>u32</type>
      <name>z001_func</name>
      <anchor>a20</anchor>
      <arglist>(struct i2c_adapter *adapter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>men16z001_pause</name>
      <anchor>a21</anchor>
      <arglist>(unsigned int amount)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>z001_probe</name>
      <anchor>a26</anchor>
      <arglist>(CHAMELEON_UNIT_T *chu)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>z001_remove</name>
      <anchor>a27</anchor>
      <arglist>(CHAMELEON_UNIT_T *chu)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int __init</type>
      <name>z001_smb_init</name>
      <anchor>a28</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void __exit</type>
      <name>z001_smb_exit</name>
      <anchor>a29</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>i2c_algorithm</type>
      <name>smbus_algorithm</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z001_smb.h</name>
    <path>/opt/menlinux/DRIVERS/Z001_SMB/</path>
    <filename>z001__smb_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SMBHSI</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBHCBC</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBSTS</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCMD</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBSTART</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBADR</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBDAA</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBDAB</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBBLK</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBHCMD</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBBYP</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_149KHZ</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_74KHZ</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_37KHZ</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_223KHZ</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_111KHZ</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBCLK_55KHZ</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBHCBC_IDLE_BASECLK64</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBHCBC_IDLE_BASECLK32</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SMBHCBC_IDLE_BASECLK128</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_ABORT</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_TOUT</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_QUICK</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_BYTE</name>
      <anchor>a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_BYTE_DATA</name>
      <anchor>a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_WORD_DATA</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_BLOCK_DATA</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_CMD_BLOCK_CLR</name>
      <anchor>a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_IDLE</name>
      <anchor>a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_BUSY</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_DONE</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_DEV</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_COLL</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_TERM</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_STS_ERR</name>
      <anchor>a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_HSI_HCIE</name>
      <anchor>a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA16Z001_HSI_IE</name>
      <anchor>a38</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z001_smb_doc.c</name>
    <path>/opt/menlinux/DRIVERS/Z001_SMB/</path>
    <filename>z001__smb__doc_8c</filename>
  </compound>
  <compound kind="struct">
    <name>Z001_DRVDATA_T</name>
    <filename>structZ001__DRVDATA__T.html</filename>
  </compound>
  <compound kind="page">
    <name>z001dummy</name>
    <title>MEN logo</title>
    <filename>z001dummy</filename>
  </compound>
</tagfile>
