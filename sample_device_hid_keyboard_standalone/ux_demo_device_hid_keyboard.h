/***************************************************************************
 * Copyright (c) 2025-present Eclipse ThreadX Contributors
 *
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 *
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/**  AUTHOR                                                               */
/**                                                                       */
/**   Mohamed AYED                                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#ifndef UX_DEMO_DEVICE_HID_KEYBOARD_H
#define UX_DEMO_DEVICE_HID_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ux_api.h"
#include "ux_device_class_hid.h"


#include "ux_demo_device_hid_descriptors.h"

#include "common_hardware_code.h"
#include "usb_app_setup.h"


#define DEMO_STACK_SIZE                         2*1024
#define UX_DEVICE_MEMORY_STACK_SIZE             2*1024

#define UX_HID_NUM_LOCK_MASK                    0x01
#define UX_HID_CAPS_LOCK_MASK                   0x02


#define UX_DEMO_HID_KEYBOARD_SEND_LOWCASE_CHARATER      0x00
#define UX_DEMO_HID_KEYBOARD_SEND_UPPERCASE_CHARATER    0x01
#define UX_DEMO_HID_KEYBOARD_SEND_NUMBER                0x02
#define UX_DEMO_HID_KEYBOARD_SENLD_SPECIAL_CHARATER     0x03

#define UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE            0x10
#define UX_DEMO_HID_KEYBOARD_SEND_EVENT_FINISH          0x11

UCHAR keys_alphanumeric[] = {
    0x00,       /*  HID KEY NONE  */
    0x04,       /*  HID KEY A     */
    0x05,       /*  HID KEY B     */
    0x06,       /*  HID KEY C     */
    0x07,       /*  HID KEY D     */
    0x08,       /*  HID KEY E     */
    0x09,       /*  HID KEY F     */
    0x0A,       /*  HID KEY G     */
    0x0B,       /*  HID KEY H     */
    0x0C,       /*  HID KEY I     */
    0x0D,       /*  HID KEY J     */
    0x0E,       /*  HID KEY K     */
    0x0F,       /*  HID KEY L     */
    0x10,       /*  HID KEY M     */
    0x11,       /*  HID KEY N     */
    0x12,       /*  HID KEY O     */
    0x13,       /*  HID KEY P     */
    0x14,       /*  HID KEY Q     */
    0x15,       /*  HID KEY R     */
    0x16,       /*  HID KEY S     */
    0x17,       /*  HID KEY T     */
    0x18,       /*  HID KEY U     */
    0x19,       /*  HID KEY V     */
    0x1A,       /*  HID KEY W     */
    0x1B,       /*  HID KEY X     */
    0x1C,       /*  HID KEY Y     */
    0x1D        /*  HID KEY Z     */
};

UCHAR keys_numeric[] = {
    0x1E,       /*  HID KEY 1     */
    0x1F,       /*  HID KEY 2     */
    0x20,       /*  HID KEY 3     */
    0x21,       /*  HID KEY 4     */
    0x22,       /*  HID KEY 5     */
    0x23,       /*  HID KEY 6     */
    0x24,       /*  HID KEY 7     */
    0x25,       /*  HID KEY 8     */
    0x26,       /*  HID KEY 9     */
    0x27        /*  HID KEY 0     */
};

UCHAR keys_others[] = {
    0x28,       /*  HID KEY ENTER                       */
    0x29,       /*  HID KEY ESCAPE                      */
    0x2A,       /*  HID KEY BACKSPACE                   */
    0x2B,       /*  HID KEY TAB                         */
    0x2C,       /*  HID KEY SPACE                       */
    0x2D,       /*  HID KEY MINUS                       */
    0x2E,       /*  HID KEY EQUAL                       */
    0x2F,       /*  HID KEY BRACKET_LEFT                */
    0x30,       /*  HID KEY BRACKET_RIGHT               */
    0x31,       /*  HID KEY BACKSLASH                   */
    0x32,       /*  HID KEY EUROPE_1                    */
    0x33,       /*  HID KEY SEMICOLON                   */
    0x34,       /*  HID KEY APOSTROPHE                  */
    0x35,       /*  HID KEY GRAVE                       */
    0x36,       /*  HID KEY COMMA                       */
    0x37,       /*  HID KEY PERIOD                      */
    0x38,       /*  HID KEY SLASH                       */
    0x39,       /*  HID KEY CAPS_LOCK                   */
    0x3A,       /*  HID KEY F1                          */
    0x3B,       /*  HID KEY F2                          */
    0x3C,       /*  HID KEY F3                          */
    0x3D,       /*  HID KEY F4                          */
    0x3E,       /*  HID KEY F5                          */
    0x3F,       /*  HID KEY F6                          */
    0x40,       /*  HID KEY F7                          */
    0x41,       /*  HID KEY F8                          */
    0x42,       /*  HID KEY F9                          */
    0x43,       /*  HID KEY F10                         */
    0x44,       /*  HID KEY F11                         */
    0x45,       /*  HID KEY F12                         */
    0x46,       /*  HID KEY PRINT_SCREEN                */
    0x47,       /*  HID KEY SCROLL_LOCK                 */
    0x48,       /*  HID KEY PAUSE                       */
    0x49,       /*  HID KEY INSERT                      */
    0x4A,       /*  HID KEY HOME                        */
    0x4B,       /*  HID KEY PAGE_UP                     */
    0x4C,       /*  HID KEY DELETE                      */
    0x4D,       /*  HID KEY END                         */
    0x4E,       /*  HID KEY PAGE_DOWN                   */
    0x4F,       /*  HID KEY ARROW_RIGHT                 */
    0x50,       /*  HID KEY ARROW_LEFT                  */
    0x51,       /*  HID KEY ARROW_DOWN                  */
    0x52,       /*  HID KEY ARROW_UP                    */
    0x53,       /*  HID KEY NUM_LOCK                    */
    0x54,       /*  HID KEY KEYPAD_DIVIDE               */
    0x55,       /*  HID KEY KEYPAD_MULTIPLY             */
    0x56,       /*  HID KEY KEYPAD_SUBTRACT             */
    0x57,       /*  HID KEY KEYPAD_ADD                  */
    0x58,       /*  HID KEY KEYPAD_ENTER                */
    0x59,       /*  HID KEY KEYPAD_1                    */
    0x5A,       /*  HID KEY KEYPAD_2                    */
    0x5B,       /*  HID KEY KEYPAD_3                    */
    0x5C,       /*  HID KEY KEYPAD_4                    */
    0x5D,       /*  HID KEY KEYPAD_5                    */
    0x5E,       /*  HID KEY KEYPAD_6                    */
    0x5F,       /*  HID KEY KEYPAD_7                    */
    0x60,       /*  HID KEY KEYPAD_8                    */
    0x61,       /*  HID KEY KEYPAD_9                    */
    0x62,       /*  HID KEY KEYPAD_0                    */
    0x63,       /*  HID KEY KEYPAD_DECIMAL              */
    0x64,       /*  HID KEY EUROPE_2                    */
    0x65,       /*  HID KEY APPLICATION                 */
    0x66,       /*  HID KEY POWER                       */
    0x67,       /*  HID KEY KEYPAD_EQUAL                */
    0x68,       /*  HID KEY F13                         */
    0x69,       /*  HID KEY F14                         */
    0x6A,       /*  HID KEY F15                         */
    0x6B,       /*  HID KEY F16                         */
    0x6C,       /*  HID KEY F17                         */
    0x6D,       /*  HID KEY F18                         */
    0x6E,       /*  HID KEY F19                         */
    0x6F,       /*  HID KEY F20                         */
    0x70,       /*  HID KEY F21                         */
    0x71,       /*  HID KEY F22                         */
    0x72,       /*  HID KEY F23                         */
    0x73,       /*  HID KEY F24                         */
    0x74,       /*  HID KEY EXECUTE                     */
    0x75,       /*  HID KEY HELP                        */
    0x76,       /*  HID KEY MENU                        */
    0x77,       /*  HID KEY SELECT                      */
    0x78,       /*  HID KEY STOP                        */
    0x79,       /*  HID KEY AGAIN                       */
    0x7A,       /*  HID KEY UNDO                        */
    0x7B,       /*  HID KEY CUT                         */
    0x7C,       /*  HID KEY COPY                        */
    0x7D,       /*  HID KEY PASTE                       */
    0x7E,       /*  HID KEY FIND                        */
    0x7F,       /*  HID KEY MUTE                        */
    0x80,       /*  HID KEY VOLUME_UP                   */
    0x81,       /*  HID KEY VOLUME_DOWN                 */
    0x82,       /*  HID KEY LOCKING_CAPS_LOCK           */
    0x83,       /*  HID KEY LOCKING_NUM_LOCK            */
    0x84,       /*  HID KEY LOCKING_SCROLL_LOCK         */
    0x85,       /*  HID KEY KEYPAD_COMMA                */
    0x86,       /*  HID KEY KEYPAD_EQUAL_SIGN           */
    0x87,       /*  HID KEY KANJI1                      */
    0x88,       /*  HID KEY KANJI2                      */
    0x89,       /*  HID KEY KANJI3                      */
    0x8A,       /*  HID KEY KANJI4                      */
    0x8B,       /*  HID KEY KANJI5                      */
    0x8C,       /*  HID KEY KANJI6                      */
    0x8D,       /*  HID KEY KANJI7                      */
    0x8E,       /*  HID KEY KANJI8                      */
    0x8F,       /*  HID KEY KANJI9                      */
    0x90,       /*  HID KEY LANG1                       */
    0x91,       /*  HID KEY LANG2                       */
    0x92,       /*  HID KEY LANG3                       */
    0x93,       /*  HID KEY LANG4                       */
    0x94,       /*  HID KEY LANG5                       */
    0x95,       /*  HID KEY LANG6                       */
    0x96,       /*  HID KEY LANG7                       */
    0x97,       /*  HID KEY LANG8                       */
    0x98,       /*  HID KEY LANG9                       */
    0x99,       /*  HID KEY ALTERNATE_ERASE             */
    0x9A,       /*  HID KEY SYSREQ_ATTENTION            */
    0x9B,       /*  HID KEY CANCEL                      */
    0x9C,       /*  HID KEY CLEAR                       */
    0x9D,       /*  HID KEY PRIOR                       */
    0x9E,       /*  HID KEY RETURN                      */
    0x9F,       /*  HID KEY SEPARATOR                   */
    0xA0,       /*  HID KEY OUT                         */
    0xA1,       /*  HID KEY OPER                        */
    0xA2,       /*  HID KEY CLEAR_AGAIN                 */
    0xA3,       /*  HID KEY CRSEL_PROPS                 */
    0xA4,       /*  HID KEY EXSEL                       */
    0xB0,       /*  HID_KEY_KEYPAD_00                   */
    0xB1,       /*  HID_KEY_KEYPAD_000                  */
    0xB2,       /*  HID_KEY_THOUSANDS_SEPARATOR         */
    0xB3,       /*  HID_KEY_DECIMAL_SEPARATOR           */
    0xB4,       /*  HID_KEY_CURRENCY_UNIT               */
    0xB5,       /*  HID_KEY_CURRENCY_SUBUNIT            */
    0xB6,       /*  HID_KEY_KEYPAD_LEFT_PARENTHESIS     */
    0xB7,       /*  HID_KEY_KEYPAD_RIGHT_PARENTHESIS    */
    0xB8,       /*  HID_KEY_KEYPAD_LEFT_BRACE           */
    0xB9,       /*  HID_KEY_KEYPAD_RIGHT_BRACE          */
    0xBA,       /*  HID_KEY_KEYPAD_TAB                  */
    0xBB,       /*  HID_KEY_KEYPAD_BACKSPACE            */
    0xBC,       /*  HID_KEY_KEYPAD_A                    */
    0xBD,       /*  HID_KEY_KEYPAD_B                    */
    0xBE,       /*  HID_KEY_KEYPAD_C                    */
    0xBF,       /*  HID_KEY_KEYPAD_D                    */
    0xC0,       /*  HID_KEY_KEYPAD_E                    */
    0xC1,       /*  HID_KEY_KEYPAD_F                    */
    0xC2,       /*  HID_KEY_KEYPAD_XOR                  */
    0xC3,       /*  HID_KEY_KEYPAD_CARET                */
    0xC4,       /*  HID_KEY_KEYPAD_PERCENT              */
    0xC5,       /*  HID_KEY_KEYPAD_LESS_THAN            */
    0xC6,       /*  HID_KEY_KEYPAD_GREATER_THAN         */
    0xC7,       /*  HID_KEY_KEYPAD_AMPERSAND            */
    0xC8,       /*  HID_KEY_KEYPAD_DOUBLE_AMPERSAND     */
    0xC9,       /*  HID_KEY_KEYPAD_VERTICAL_BAR         */
    0xCA,       /*  HID_KEY_KEYPAD_DOUBLE_VERTICAL_BAR  */
    0xCB,       /*  HID_KEY_KEYPAD_COLON                */
    0xCC,       /*  HID_KEY_KEYPAD_HASH                 */
    0xCD,       /*  HID_KEY_KEYPAD_SPACE                */
    0xCE,       /*  HID_KEY_KEYPAD_AT                   */
    0xCF,       /*  HID_KEY_KEYPAD_EXCLAMATION          */
    0xD0,       /*  HID_KEY_KEYPAD_MEMORY_STORE         */
    0xD1,       /*  HID_KEY_KEYPAD_MEMORY_RECALL        */
    0xD2,       /*  HID_KEY_KEYPAD_MEMORY_CLEAR         */
    0xD3,       /*  HID_KEY_KEYPAD_MEMORY_ADD           */
    0xD4,       /*  HID_KEY_KEYPAD_MEMORY_SUBTRACT      */
    0xD5,       /*  HID_KEY_KEYPAD_MEMORY_MULTIPLY      */
    0xD6,       /*  HID_KEY_KEYPAD_MEMORY_DIVIDE        */
    0xD7,       /*  HID_KEY_KEYPAD_PLUS_MINUS           */
    0xD8,       /*  HID_KEY_KEYPAD_CLEAR                */
    0xD9,       /*  HID_KEY_KEYPAD_CLEAR_ENTRY          */
    0xDA,       /*  HID_KEY_KEYPAD_BINARY               */
    0xDB,       /*  HID_KEY_KEYPAD_OCTAL                */
    0xDC,       /*  HID_KEY_KEYPAD_DECIMAL_2            */
    0xDD,       /*  HID_KEY_KEYPAD_HEXADECIMAL          */
    0xE0,       /*  HID_KEY_CONTROL_LEFT                */
    0xE1,       /*  HID_KEY_SHIFT_LEFT                  */
    0xE2,       /*  HID_KEY_ALT_LEFT                    */
    0xE3,       /*  HID_KEY_GUI_LEFT                    */
    0xE4,       /*  HID_KEY_CONTROL_RIGHT               */
    0xE5,       /*  HID_KEY_SHIFT_RIGHT                 */
    0xE6,       /*  HID_KEY_ALT_RIGHT                   */
    0xE7        /*  HID_KEY_GUI_RIGHT                   */
};

#ifdef __cplusplus
}
#endif
#endif /* UX_DEMO_DEVICE_HID_KEYBOARD_H */
