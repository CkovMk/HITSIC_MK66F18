#pragma once
#ifndef _DRV_EXTINT_HPP_
#define _DRV_EXTINT_HPP_

#include "inc_fsl_rt1052.h"
#include "inc_stdlib.h"
#include "inc_gnc.h"

class extInt_t
{
public:
	typedef void (*handler_t)(void);

	static std::map<uint32_t, std::map<uint32_t, extInt_t>> isrSet;
	static extInt_t& insert(GPIO_Type* _gpio, uint32_t _pin, handler_t _handler, gpio_interrupt_mode_t _mode, bool _enable);
	static void isr(GPIO_Type* _gpio);

	GPIO_Type* gpio;
	uint32_t pin;
	handler_t handler;
	gpio_interrupt_mode_t mode;

	void setup(GPIO_Type* _gpio, uint32_t _pin, handler_t _handler, gpio_interrupt_mode_t _mode, bool _enable);

	void setMode(gpio_interrupt_mode_t _mode)
	{
		mode = _mode;
		GPIO_PinSetInterruptConfig(gpio, pin, _mode);
	}
	void setEnable(bool b)
	{
		GPIO_PortEnableInterrupts(gpio, 1 << pin);
	}
	extInt_t(void);
private:
	
	extInt_t(GPIO_Type* _gpio, uint32_t _pin, handler_t _handler, gpio_interrupt_mode_t _mode, bool _enable)
	{
		setup(_gpio, _pin, _handler, _mode, _enable);
	}
};



#endif // ! _DRV_EXTINT_HPP_


