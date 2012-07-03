#include "xbee_resetter.h"
#include "subsystems/datalink/downlink.h"
#include "subsystems/datalink/datalink.h"
#include "subsystems/datalink/transport.h"
#include "print.h"
#include "generated/periodic_telemetry.h"

#ifndef DOWNLINK_DEVICE
#define DOWNLINK_DEVICE DOWNLINK_AP_DEVICE
#endif

#ifndef ALLOW_TELEMETRY_DISABLE
#error "XBee resetter module requires <define name="ALLOW_TELEMETRY_DISABLE" />"
#endif

#pragma message "Using XBee reboot module - only for 868MHz modules"

uint16_t xbee_reset_ticks;
uint8_t telemetry_mode_Ap;
uint8_t telemetry_mode_Fbw;

uint8_t old_telemetry_mode_Ap;
uint8_t old_telemetry_mode_Fbw;
bool_t disable_telemetry;

void init_xbee_resetter(void) {
	xbee_reset_ticks = 0;
}

void periodic_1Hz_xbee_resetter(void) {
	xbee_reset_ticks += 1;

	switch(xbee_reset_ticks) {
		case XBEE_RESETTER_RESET_PERIOD:
			stop_telemetry();
			break;

		case XBEE_RESETTER_RESET_PERIOD + 1:
			TransportLink(DOWNLINK_DEVICE, PrintString("+++"));
			break;

		case XBEE_RESETTER_RESET_PERIOD + 2:
			TransportLink(DOWNLINK_DEVICE, PrintString("ATFR\r\n"));
			break;

		case XBEE_RESETTER_RESET_PERIOD + 3:
			start_telemetry();
			xbee_reset_ticks = 0;
			break;
	}
}

void stop_telemetry(void) {
		disable_telemetry = TRUE;

		old_telemetry_mode_Ap = telemetry_mode_Ap;
		old_telemetry_mode_Fbw = telemetry_mode_Fbw;

		telemetry_mode_Ap = TELEMETRY_MODE_Ap_blank;
		telemetry_mode_Fbw = TELEMETRY_MODE_Fbw_blank;
}

void start_telemetry(void) {
		disable_telemetry = FALSE;

		telemetry_mode_Ap = old_telemetry_mode_Ap;
		telemetry_mode_Fbw = old_telemetry_mode_Fbw;
}

void start_xbee_resetter(void) {
}

void stop_xbee_resetter(void) {
}

