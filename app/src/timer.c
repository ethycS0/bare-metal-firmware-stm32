#include"timer.h"
#include<libopencm3/stm32/timer.h>

// freq = systemp_freq / ((prescaler - 1) * (arr - 1))
#define PRESCALER (84)
#define ARR_VAlUE (1000)


void timer_setup(void) {

        // Enable Peripheral
        rcc_periph_clock_enable(RCC_TIM2);

        // High Level Timer Configuration
        timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

        // Setup PWM Mode
        timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);

        // Enable PWM Outpput
        timer_enable_counter(TIM2);
        timer_enable_oc_output(TIM2, TIM_OC1);

        //  Setup Frequency and Resolution of PWM
        timer_set_prescaler(TIM2, PRESCALER - 1);
        timer_set_period(TIM2, ARR_VAlUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle) {
        // duty_cycle = (crr / arr) * 100

        const float raw_value = (float)ARR_VAlUE * (duty_cycle / 100.0f);
        timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);
}
