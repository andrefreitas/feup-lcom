#ifndef __SPEAKER_H
#define __SPEAKER_H

/** @defgroup speaker speaker
 * @{
 *
 * Functions that control the speaker output
 */

/**
 * @brief Enables/disables speaker
 *
 * @param on If zero disable speaker, otherwise enable it
 * @return Return 0 upon success and non-zero otherwise
 */
int speaker_ctrl(unsigned char on);

/**
 * @brief Enables/disables timer 2
 *
 * @param on If zero disable timer 2, otherwise enable it
 * @return Return 0 upon success and non-zero otherwise
 */
int speaker_timer_ctrl(unsigned char on);

/**@}*/

#endif /* __SPEAKER_H */
