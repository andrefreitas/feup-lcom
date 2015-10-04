#ifndef __TIMER_H
#define __TIMER_H

/** @defgroup timer timer
 * @{
 *
 * Functions for using the i8254 timers
 */

/**
 * @brief Configures a timer to generate a square wave 
 * 
 * @param timer Timer to configure. (Ranges from 0 to 2)
 * @param rate Frequency of the square wave to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_set_rate(unsigned long timer, unsigned long rate);

/**
 * @brief Reads the the mode in which a timer was programmed
 *
 * @param timer Timer whose status to read (Ranges from 0 to 2)
 * @param st    Address of memory position to be filled with the timer status
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_get_status(unsigned long timer, u8_t *st);

/**
 * @brief Shows the mode in which a timer was programmed
 *
 * Displays in a human friendly way, the configuration of the input
 *  timer, by providing the values (and meanings) of the different 
 *  components of a timer status information
 * 
 * @param timer Timer whose status to read (Ranges from 0 to 2)
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_show_status(unsigned long timer);

/**
 * @brief Subscribes and enables Timer 0 interrupts
 *
 * @return Returns bitmask for this interrupt, upon success, 0 upon failure
 */
unsigned long timer_subscribe_int(void );

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_unsubscribe_int();
#endif __TIMER_H
