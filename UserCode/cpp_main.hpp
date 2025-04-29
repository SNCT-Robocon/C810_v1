#ifndef CPP_MAIN_HPP_
#define CPP_MAIN_HPP_

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

#include "led_control.hpp"
#include "pwm_control.hpp"
#include "timer_interruption.hpp"
#include "uart_lib.hpp"

namespace UserCode
{
    void cpp_main_init();
    void cpp_main_while();

    void timer_interruption_10kHz();

    stmlib_v1::gpio_input hall_sensor_1(HALL_1_GPIO_Port, HALL_1_Pin);
    stmlib_v1::gpio_input hall_sensor_2(HALL_2_GPIO_Port, HALL_2_Pin);
    stmlib_v1::gpio_input hall_sensor_3(HALL_3_GPIO_Port, HALL_3_Pin);

    stmlib_v1::HardTimer hard_timer_10kHz(&htim7);

    stmlib_v1::stlink_debag stlink(&huart2, 10);

    uint16_t duty = 0;

    const uint16_t max_duty = 4249;

    bool is_started[3] = {0, 0, 0};void set_pwm_state(bool ch1, bool ch2, bool ch3);

}

#endif /* CPP_MAIN_HPP_ */