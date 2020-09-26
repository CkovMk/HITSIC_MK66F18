#pragma once
#ifndef _DRV_LCD240_HPP_
#define _DRV_LCD240_HPP_

#include "inc_fsl_rt1052.h"
#include "inc_stdlib.h"
#include "inc_gnc.h"

#include "drv_pitmgr.hpp"



class lcd240_t
{
public:
	enum statusFlag_t : uint8_t
	{
		edmaLock = 1 << 0,
		edmaDone = 1 << 1,
		edmaError = 1 << 2,
	};
	uint8_t statusFlag;
	static lcd240_t& getInst(void)
	{
		static lcd240_t inst;
		return inst;
	}

	LPSPI_Type* base;
	uint32_t edmaChnl;

	edma_handle_t edmaTxHandle;

	static void edmaCallBack(LPSPI_Type* base, lpspi_master_edma_handle_t* handle, status_t status, void* userData);


	status_t spiTxPoll(uint8_t* data, uint32_t size);
	status_t spiTxEdma(uint8_t* data, uint32_t size);
	void setConfigPoll(uint8_t* cmd, uint8_t* dat, uint32_t size);
	void setRST(uint8_t b);
	void setD_C(uint8_t b);
	void setBKL(uint8_t b);


	void setup(void);
	void setRange(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
	void fill(uint16_t col);


private:
	lcd240_t(void);

};



#endif // ! _DRV_LCD240_HPP_
