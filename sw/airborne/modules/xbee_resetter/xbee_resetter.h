/** \file xbee_resetter.h
 *
 * Resets an xbee 
 */

#ifndef XBEE_RESETTER_MODULE_H
#define XBEE_RESETTER_MODULE_H

#ifndef XBEE_RESETTER_LED
#define XBEE_RESETTER_LED 9
#endif

#ifndef XBEE_RESETTER_RESET_PERIOD
#define XBEE_RESETTER_RESET_PERIOD 300
#endif

void init_xbee_resetter(void);
void periodic_1Hz_xbee_resetter(void);
void start_xbee_resetter(void);
void stop_xbee_resetter(void);
void reset_string(void);

#endif
