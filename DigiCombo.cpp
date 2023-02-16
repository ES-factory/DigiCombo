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

#include "DigiCombo.h"
#include "DigiComboC.h"
#include "scancode_ascii_table.h"

#include <Arduino.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

Digi_Combo DigiCombo;

uint8_t Digi_Combo::countContact()
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < CONTACT_COUNT_MAXIMUM; i++) if (contacts[i]) count++;
    return count;
}

void Digi_Combo::begin()
{
    usbBegin();
    delay(1000);
}

void Digi_Combo::poll()
{
    usbPollWrapper();
}

void Digi_Combo::delay(unsigned long durationMs)
{
    unsigned long last = millis();
    while (durationMs > 0) {
        unsigned long now = millis();
        durationMs -= now - last;
        last = now;
        poll();
    }
}

void Digi_Combo::moveFinger(uint16_t x, uint16_t y, uint8_t contactId)
{
    uint8_t id = contactId != 0xFF ? contactId : lastContactId;
    contacts[id] = 1;

    report_buffer[0] = REPORT_ID_TOUCH;
    report_buffer[1] = 1;
    report_buffer[2] = id;
    report_buffer[3] = 0b11;
    report_buffer[4] = MSB(x);
    report_buffer[5] = LSB(x);
    report_buffer[6] = MSB(y);
    report_buffer[7] = LSB(y);
    usbReportSend(REPORT_SIZE_TOUCH);
}

void Digi_Combo::tapSingle(uint16_t x, uint16_t y, uint16_t duration, uint8_t contactId)
{
    moveFinger(x, y, contactId);
    delay(duration);
    release(contactId);
}

void Digi_Combo::pressKey(uint8_t keycode, uint8_t modifiers)
{
    report_buffer[0] = REPORT_ID_KEYBOARD;
    report_buffer[1] = modifiers;
    report_buffer[2] = keycode;
    usbReportSend(REPORT_SIZE_KEYBOARD);
}

void Digi_Combo::sendKeyStroke(uint8_t keycode, uint8_t modifiers)
{
    pressKey(keycode, modifiers);
    pressKey(0, 0);
}

void Digi_Combo::release(uint8_t contactId)
{
    uint8_t id = contactId != 0xFF ? contactId : lastContactId;
    uint8_t currentlyCountContact = countContact();
    if (lastReportId == REPORT_ID_TOUCH) contacts[id] = 0;

    report_buffer[0] = lastReportId;
    report_buffer[1] = lastReportId == REPORT_ID_TOUCH ? currentlyCountContact : 0;
    report_buffer[2] = lastReportId == REPORT_ID_TOUCH ? id : 0;
    report_buffer[3] = 0;
    report_buffer[4] = 0;
    report_buffer[5] = 0;
    report_buffer[6] = 0;
    report_buffer[7] = 0;

    usbReportSend(BUFFER_SIZE);
}

size_t Digi_Combo::write(uint8_t ascii)
{
    uint8_t data = pgm_read_byte_near(ascii_to_scan_code_table + (ascii - 8));
    sendKeyStroke(data & 0b01111111, data >> 7 ? MOD_RIGHT_SHIFT : 0);
    return 1;
}
