#ifndef MCU_INIT_H
#define MCU_INIT_H

#define WDT_TIMEOUT_MS 5000

/**
 * @brief Initialization of common microcontroller functionality that affects all peripherals
 * (e.g. watchdog, clocks, pins)
 */
void mcu_init(void);

#endif /* MCU_INIT_H */