/*
 * pwm.h
 *
 * Created: 2017-10-25 2:37:09 PM
 *  Author: abates
 */ 


#ifndef PWM_H_
#define PWM_H_

typedef enum{
	Brake_to_VCC,
	DC_Motor_Clockwise,
	DC_Motor_Counter_Clockwise,
	Brake_to_Ground
}Motor_Setting;

extern void init_pwm();
extern void set_dc_motor_speed(uint8_t speed);
extern void set_motor_setting(Motor_Setting setting);

#endif /* PWM_H_ */