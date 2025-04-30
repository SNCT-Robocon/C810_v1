#include "cpp_main.hpp"


void wrap_cpp_main_init(void){
    UserCode::cpp_main_init();
}

void wrap_cpp_main_while(void){
    UserCode::cpp_main_while();
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim == UserCode::hard_timer_10kHz.get_handle()){
        UserCode::hard_timer_10kHz.handle_callback();
    }
}



namespace UserCode
{

    //bool ok = false;

    void cpp_main_init(){

        hard_timer_10kHz.set_callback(timer_interruption_10kHz);
        hard_timer_10kHz.start();

        stlink.transmit_debug("init finished\r\n");

    }

    void cpp_main_while(){

        //stlink.transmit_debug("in the while\r\n");

        //stlink.transmit_debug("ok is %d \r\n", ok);

        duty = 1000;

    }

    void timer_interruption_10kHz(){

        //ok = true;

        uint8_t state = hall_sensor_1.get_state() << 2 | hall_sensor_2.get_state() << 1 | hall_sensor_3.get_state();

        switch(state){
                
            case 0b001 : {
                
                set_pwm_state(false, true, true);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, duty);
                
                break;
            }
            
            case 0b011 : {

                set_pwm_state(true, false, true);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, duty);

                break;
            }

            case 0b010 : {

                set_pwm_state(true, true, false);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

                break;
            }

            case 0b110 : {

                set_pwm_state(false, true, true);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

                break;
            }

            case 0b100 : {

                set_pwm_state(true, false, true);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

                break;
            }

            case 0b101 : {

                set_pwm_state(true, true, false);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

                break;
            }
            
            default : {

                set_pwm_state(false, false, false);

                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

                break;
            }
        }


        

    }


    void set_pwm_state(bool ch1, bool ch2, bool ch3){

        if(is_started[0] == false && ch1 == true){
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
            is_started[0] = true;
        }
        else if (is_started[0] == true && ch1 == false){
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
            is_started[0] = false;
        }


        if(is_started[1] == false && ch2 == true){
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
            is_started[1] = true;
        }
        else if (is_started[1] == true && ch2 == false){
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
            is_started[1] = false;
        }


        if(is_started[2] == false && ch3 == true){
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
            is_started[2] = true;
        }
        else if (is_started[2] == true && ch3 == false){
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
            is_started[2] = false;
        }


    }   
}