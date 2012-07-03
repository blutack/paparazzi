#include "xbee_resetter.h"
#include "led.h"
#include "subsystems/datalink/downlink.h"
#include "subsystems/datalink/datalink.h"
#include "mcu_periph/sys_time.h"
#include "subsystems/datalink/transport.h"
#include "mcu_periph/uart.h"
#include "print.h"
#include "firmwares/fixedwing/autopilot.h"
#include "generated/periodic_telemetry.h"

#ifndef DOWNLINK_DEVICE
#define DOWNLINK_DEVICE DOWNLINK_AP_DEVICE
#endif

#pragma message "Using XBee reboot module - only for 868MHz modules"

uint16_t xbee_reset_ticks;
uint8_t telemetry_mode_Ap;
bool_t dl_msg_available;

void init_xbee_resetter(void) {
  LED_INIT(XBEE_RESETTER_LED);
  LED_OFF(XBEE_RESETTER_LED);
	xbee_reset_ticks = 0;
	dl_msg_available = TRUE;
}

void periodic_1Hz_xbee_resetter(void) {
	xbee_reset_ticks += 1;
	if(xbee_reset_ticks >= XBEE_RESETTER_RESET_PERIOD) {
		//reset_string();
		//disable_telemetry = TRUE;
		telemetry_mode_Ap = TELEMETRY_MODE_Ap_blank;
		telemetry_mode_Fbw = TELEMETRY_MODE_Fbw_blank;
		dl_msg_available = FALSE;
		xbee_reset_ticks = 0;
	}
}

void reset_string(void) {
	sys_time_usleep(1000000);
	TransportLink(DOWNLINK_DEVICE, PrintString("+++"));
	sys_time_usleep(1100000);
	TransportLink(DOWNLINK_DEVICE, PrintString("ATFR\r\n"));
	sys_time_usleep(10000);
}

void start_xbee_resetter(void) {
}

void stop_xbee_resetter(void) {
}

