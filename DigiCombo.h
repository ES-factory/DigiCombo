/*
 * Copyright (C) 2023  ES factory
 *
 * DigiCombo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DigiCombo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DigiCombo.  If not, see https://www.gnu.org/licenses/.
 */

#ifndef __DIGICOMBO_H__
#define __DIGICOMBO_H__

#include <stdint.h>
#include <Print.h>

class Digi_Combo : public Print {
  private:
    uint8_t lastContactId = 0;
    uint8_t countContact();
    void poll();
  public:
    /* Initial setup to be known as USB-HID. */
    void begin(); 

    /**
     * Provides a special type of delay that prevents the system from generating 
     * an unknown USB error and should be used instead of the common function.
     *
     * @param durationMs in milisecond unit 
     */
    void delay(unsigned long durationMs);

    /**
     * By specifying the coordinates on the screen as a percentage, 
     * it keeps them until the release function is called.
     *
     * @param x in x-axis in range 0..10000 any 100 value reperesents 1 percent
     * @param y in y-axis in range 0..10000 any 100 value reperesents 1 percent
     * @param contactId The default value shows the last contactId else one of CONTACT_ONE..TEN
     */
    void moveFinger(uint16_t x, uint16_t y, uint8_t contactId = 0xFF);

    /**
     * To touch a specific location for a specific amount of time.
     *
     * @param x in x-axis in range 0..10000 any 100 value reperesents 1 percent
     * @param y in y-axis in range 0..10000 any 100 value reperesents 1 percent
     * @param durationMs in milisecond unit 
     * @param contactId The default value shows the last contactId else one of CONTACT_ONE..TEN
     */
    void tapSingle(uint16_t x, uint16_t y, uint16_t duration = 50, uint8_t contactId = 0xFF);

    /**
     * Presses and holds a set of keyboard keys until the release function is called.
     *
     * @param keycode includes KEYCODE_* for useing more than one compose them with OR operation 
     * @param modifiers includes MOD_* for useing more than one compose them with OR operation 
     */
    void pressKey(uint8_t keycode, uint8_t modifiers = 0);

    /**
     * To send a set of keyboard keys, the result of which you can see immediately.
     * 
     * @param keycode includes KEYCODE_* for useing more than one compose them with OR operation 
     * @param modifiers includes MOD_* for useing more than one compose them with OR operation 
     */
    void sendKeyStroke(uint8_t keycode, uint8_t modifiers = 0);
    void release(uint8_t contactId = 0xFF);

    /* To print a character. */
		virtual size_t write(uint8_t);
		using Print::write;
		
    /* To print a text. */
		using Print::print;

    /* To print a text with a new line. */
		using Print::println;
};

extern Digi_Combo DigiCombo;

#define LSB(v) ((v >> 8) & 0xff)
#define MSB(v) (v & 0xff)

#define CONTACT_ONE 0
#define CONTACT_TWO 1
#define CONTACT_THREE 2
#define CONTACT_FOUR 3
#define CONTACT_FIVE 4
#define CONTACT_SIX 5
#define CONTACT_SEVEN 6
#define CONTACT_EIGHT 7
#define CONTACT_NINE 8
#define CONTACT_TEN 9
#define DEFAULT_CONTACT CONTACT_ONE

#define MOD_LEFT_CONTROL	0x01
#define MOD_LEFT_SHIFT		0x02
#define MOD_LEFT_ALT		0x04
#define MOD_LEFT_GUI		0x08
#define MOD_RIGHT_CONTROL	0x10
#define MOD_RIGHT_SHIFT		0x20
#define MOD_RIGHT_ALT		0x40
#define MOD_RIGHT_GUI		0x80

#define KEYCODE_LEFT_CONTROL	                0xE0
#define KEYCODE_LEFT_SHIFT		        0xE1
#define KEYCODE_LEFT_ALT		        0xE2
#define KEYCODE_LEFT_GUI		        0xE3
#define KEYCODE_RIGHT_CONTROL	                0xE4
#define KEYCODE_RIGHT_SHIFT		        0xE5
#define KEYCODE_RIGHT_ALT		        0xE6
#define KEYCODE_RIGHT_GUI		        0xE7
#define KEYCODE_1				0x1E
#define KEYCODE_2				0x1F
#define KEYCODE_3				0x20
#define KEYCODE_4				0x21
#define KEYCODE_5				0x22
#define KEYCODE_6				0x23
#define KEYCODE_7				0x24
#define KEYCODE_8				0x25
#define KEYCODE_9				0x26
#define KEYCODE_0				0x27
#define KEYCODE_A				0x04
#define KEYCODE_B				0x05
#define KEYCODE_C				0x06
#define KEYCODE_D				0x07
#define KEYCODE_E				0x08
#define KEYCODE_F				0x09
#define KEYCODE_G				0x0A
#define KEYCODE_H				0x0B
#define KEYCODE_I				0x0C
#define KEYCODE_J				0x0D
#define KEYCODE_K				0x0E
#define KEYCODE_L				0x0F
#define KEYCODE_M				0x10
#define KEYCODE_N				0x11
#define KEYCODE_O				0x12
#define KEYCODE_P				0x13
#define KEYCODE_Q				0x14
#define KEYCODE_R				0x15
#define KEYCODE_S				0x16
#define KEYCODE_T				0x17
#define KEYCODE_U				0x18
#define KEYCODE_V				0x19
#define KEYCODE_W				0x1A
#define KEYCODE_X				0x1B
#define KEYCODE_Y				0x1C
#define KEYCODE_Z				0x1D
#define KEYCODE_COMMA			0x36
#define KEYCODE_PERIOD			0x37
#define KEYCODE_MINUS			0x2D
#define KEYCODE_EQUAL			0x2E
#define KEYCODE_BACKSLASH		0x31
#define KEYCODE_SQBRAK_LEFT		0x2F
#define KEYCODE_SQBRAK_RIGHT	0x30
#define KEYCODE_SLASH			0x38
#define KEYCODE_F1				0x3A
#define KEYCODE_F2				0x3B
#define KEYCODE_F3				0x3C
#define KEYCODE_F4				0x3D
#define KEYCODE_F5				0x3E
#define KEYCODE_F6				0x3F
#define KEYCODE_F7				0x40
#define KEYCODE_F8				0x41
#define KEYCODE_F9				0x42
#define KEYCODE_F10				0x43
#define KEYCODE_F11				0x44
#define KEYCODE_F12				0x45
#define KEYCODE_APP				0x65
#define KEYCODE_ENTER			0x28
#define KEYCODE_BACKSPACE		0x2A
#define KEYCODE_ESC				0x29
#define KEYCODE_TAB				0x2B
#define KEYCODE_SPACE			0x2C
#define KEYCODE_INSERT			0x49
#define KEYCODE_HOME			0x4A
#define KEYCODE_PAGE_UP			0x4B
#define KEYCODE_DELETE			0x4C
#define KEYCODE_END				0x4D
#define KEYCODE_PAGE_DOWN		0x4E
#define KEYCODE_PRINTSCREEN		0x46
#define KEYCODE_ARROW_RIGHT		0x4F
#define KEYCODE_ARROW_LEFT		0x50
#define KEYCODE_ARROW_DOWN		0x51
#define KEYCODE_ARROW_UP		0x52

#endif 
