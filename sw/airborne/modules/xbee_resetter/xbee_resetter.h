/** \file xbee_resetter.h
 *
 * Resets an xbee 
 */

#ifndef XBEE_RESETTER_MODULE_H
#define XBEE_RESETTER_MODULE_H

#ifndef XBEE_RESETTER_RESET_PERIOD
#define XBEE_RESETTER_RESET_PERIOD 30
#endif

void init_xbee_resetter(void);
void periodic_1Hz_xbee_resetter(void);
void start_xbee_resetter(void);
void stop_xbee_resetter(void);
void stop_telemetry(void);
void start_telemetry(void);

#endif
