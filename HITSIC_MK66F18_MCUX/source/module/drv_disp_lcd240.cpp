#include <drv_disp_lcd240.hpp>

void lcd240_t::edmaCallBack(LPSPI_Type* base, lpspi_master_edma_handle_t* handle, status_t status, void* userData)
{
	lcd240_t& i = getInst();
	if (status == kStatus_Success)
	{
		i.statusFlag |= (edmaDone);
		i.statusFlag &= (~edmaError);
	}
	else
	{
		i.statusFlag &= (~edmaDone);
		i.statusFlag |= (edmaError);
#ifdef DEBUG
		throw std::runtime_error(std::string("LCD240 Edma Error"));
#endif
	}
}

void lcd240_t::setup(void)
{
	setRST(0);
	pitMgr_t::delay_ms(20);
	setRST(1);
	pitMgr_t::delay_ms(20);

	uint8_t cfgCmd;
	uint8_t cfgDat[16];

	{
		cfgCmd = 0x36;
		cfgDat[0] = 0x70;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0x3a;
		cfgDat[0] = 0x05;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xb2;
		cfgDat[0] = 0x0c;
		cfgDat[1] = 0x0c;
		cfgDat[2] = 0x00;
		cfgDat[3] = 0x33;
		cfgDat[4] = 0x33;
	}
	setConfigPoll(&cfgCmd, cfgDat, 5);

	{
		cfgCmd = 0xb7;
		cfgDat[0] = 0x35;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xbb;
		cfgDat[0] = 0x19;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xc0;
		cfgDat[0] = 0x2c;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xc1;
		cfgDat[0] = 0x01;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xc3;
		cfgDat[0] = 0x12;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xc4;
		cfgDat[0] = 0x20;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0x3c6;
		//TODO: fix this!
		cfgDat[0] = 0x0f;
	}
	setConfigPoll(&cfgCmd, cfgDat, 1);

	{
		cfgCmd = 0xd0;
		cfgDat[0] = 0xa4;
		cfgDat[1] = 0xa1;
	}
	setConfigPoll(&cfgCmd, cfgDat, 2);

	{
		cfgCmd = 0xe0;
		cfgDat[0] = 0xd0;
		cfgDat[1] = 0x04;
		cfgDat[2] = 0x0d;
		cfgDat[3] = 0x11;
		cfgDat[4] = 0x13;
		cfgDat[5] = 0x2b;
		cfgDat[6] = 0x3f;
		cfgDat[7] = 0x54;
		cfgDat[8] = 0x4c;
		cfgDat[9] = 0x18;
		cfgDat[10] = 0x0d;
		cfgDat[11] = 0x0b;
		cfgDat[12] = 0x1f;
		cfgDat[13] = 0x23;
	}
	setConfigPoll(&cfgCmd, cfgDat, 14);

	{
		cfgCmd = 0xe1;
		cfgDat[0] = 0xd0;
		cfgDat[1] = 0x04;
		cfgDat[2] = 0x0c;
		cfgDat[3] = 0x11;
		cfgDat[4] = 0x13;
		cfgDat[5] = 0x2c;
		cfgDat[6] = 0x2f;
		cfgDat[7] = 0x44;
		cfgDat[8] = 0x51;
		cfgDat[9] = 0x2f;
		cfgDat[10] = 0x1f;
		cfgDat[11] = 0x1f;
		cfgDat[12] = 0x20;
		cfgDat[13] = 0x23;
	}
	setConfigPoll(&cfgCmd, cfgDat, 14);

	{
		cfgCmd = 0x21;
	}
	setConfigPoll(&cfgCmd, cfgDat, 0);

	{
		cfgCmd = 0x11;
	}
	setConfigPoll(&cfgCmd, cfgDat, 0);

	{
		cfgCmd = 0x29;
	}
	setConfigPoll(&cfgCmd, cfgDat, 0);


}

void lcd240_t::setRange(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
	uint8_t cfgCmd;
	uint8_t cfgDat[16];
	{
		cfgCmd = (0x2a);//�е�ַ����
		cfgDat[0] = (x1);
		cfgDat[1] = (x2);
	}
	setConfigPoll(&cfgCmd, cfgDat, 2);

	{
		cfgCmd = (0x2b);//�е�ַ����
		cfgDat[0] = (y1);
		cfgDat[1] = (y2);
	}
	setConfigPoll(&cfgCmd, cfgDat, 2);

	{
		cfgCmd = (0x2c);//������д
	}
	setConfigPoll(&cfgCmd, cfgDat, 0);
}

void lcd240_t::fill(uint16_t col)
{
	setRange(0, 0, 239, 239);
	setD_C(1);
	for (uint16_t i = 0; i < 240; ++i)
	{
		for (uint16_t j = 0; j < 240; ++j)
		{
			spiTxPoll((uint8_t*)(&col),2);
		}
	}
}

lcd240_t::lcd240_t(void)
{
	base = LPSPI4;
	edmaChnl = 3;
	EDMA_CreateHandle(&edmaTxHandle, DMA0, edmaChnl);
}

status_t lcd240_t::spiTxPoll(uint8_t* data, uint32_t size)
{
	if (statusFlag & edmaLock)
	{
		return kStatus_Fail;
	}
	static lpspi_transfer_t xfer;
	{
		xfer.txData = data;
		xfer.rxData = NULL;
		xfer.dataSize = size;
		xfer.configFlags = kLPSPI_MasterPcs0;
	}
	LPSPI_MasterTransferBlocking(base, &xfer);
	return kStatus_Success;
}

status_t lcd240_t::spiTxEdma(uint8_t* data, uint32_t size)
{
	if (statusFlag & edmaLock)
	{
		return kStatus_Fail;
	}
	statusFlag ^= edmaLock;
	static lpspi_transfer_t xfer;
	{
		xfer.txData = data;
		xfer.rxData = NULL;
		xfer.dataSize = size;
		xfer.configFlags = kLPSPI_MasterPcs0;
	}
	static lpspi_master_edma_handle_t handle;
	LPSPI_MasterTransferCreateHandleEDMA(base, &handle, edmaCallBack, NULL, NULL /* No Rx Operation */, &edmaTxHandle);
	LPSPI_MasterTransferEDMA(base, &handle, &xfer);
	return kStatus_Success;
}

 void lcd240_t::setConfigPoll(uint8_t* cmd, uint8_t* dat, uint32_t dataSize)
{
	setD_C(0);
	spiTxPoll(cmd, 1);
	if (dataSize == 0) { return; }
	setD_C(1);
	spiTxPoll(dat, dataSize);
}

void lcd240_t::setRST(uint8_t b)
{
	GPIO_PinWrite(RTE_DISP_RST_GPIO, RTE_DISP_RST_PIN, b);
}

void lcd240_t::setD_C(uint8_t b)
{
	GPIO_PinWrite(RTE_DISP_D_C_GPIO, RTE_DISP_D_C_PIN, b);
}

void lcd240_t::setBKL(uint8_t b)
{
	GPIO_PinWrite(RTE_DISP_BKL_GPIO, RTE_DISP_BKL_PIN, 1);
}
