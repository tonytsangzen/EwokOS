#ifndef KEYDEF_H
#define KEYDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_ROLL_BACK       0xF1 
#define KEY_ROLL_FORWARD    0xF2
#define CONSOLE_LEFT        8

#define KEY_ESC             27
#define KEY_BACKSPACE       127
#define KEY_ENTER           13
#define KEY_SPACE           32

#define KEY_RIGHT           4
#define KEY_UP              5
#define KEY_LEFT            19
#define KEY_DOWN            24

#define KEY_POWER           26
#define KEY_HOME            0xF0 

#define KEY_BUTTON_A        97
#define KEY_BUTTON_B        98
#define KEY_BUTTON_L1       102
#define KEY_BUTTON_L2       104
#define KEY_BUTTON_MODE     110
#define KEY_BUTTON_R1       103
#define KEY_BUTTON_R2       105
#define KEY_BUTTON_SELECT   109
#define KEY_BUTTON_START    108
#define KEY_BUTTON_THUMBL   106
#define KEY_BUTTON_THUMBR   107

#define KEY_BUTTON_X        120
#define KEY_BUTTON_Y        121

#define JOYSTICK_UP        0x1
#define JOYSTICK_DOWN      0x2
#define JOYSTICK_LEFT      0x4
#define JOYSTICK_RIGHT     0x8
#define JOYSTICK_PRESS     0x10
#define JOYSTICK_BTN_A     0x10
#define JOYSTICK_BTN_B     0x20
#define JOYSTICK_BTN_SELECT    0x40
#define JOYSTICK_BTN_START     0x80

#ifdef __cplusplus
}
#endif

#endif
