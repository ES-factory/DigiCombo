# Recording android touch events for replay
A script is provided to convert recorded events from android to an arduino sketch. 

If you do not follow the setup section the scale of your recording may be off.

Multi-touch is not supported for recording


`python convert_to_code.py touch_screen_max_x touch_screen_max_y event_file.txt [optional_rounding_value=3]`

Example: 

`python .\convert_to_code.py 4095 4095 ".\examples\RecordedCurve\draw_curve_event_file.txt`

<video src='demo/draw_curve.mp4' width=180/> |


## Requirements
#### 1. Setup ADB

There are many guides on how to install adb on a computer and connect your phone.

Here is one https://www.xda-developers.com/install-adb-windows-macos-linux/

#### 2. Install Python

A working python 3 install is required 

## Setup
### 1. How to find touch_screen_max_x and touch_screen_max_y

To determine touch_screen_max_x and touch_screen_max_y run

   `adb shell getevent -il`

Find an input device that looks like a touchscreen i.e. 'sec_touchscreen' beware you may have a touchpad which is not wanted

ABS_MT_POSITION_X max is touch_screen_max_x

ABS_MT_POSITION_Y max is touch_screen_max_y

example output:
```
add device 12: /dev/input/event4
  bus:      0018
  vendor    0000
  product   0000
  version   0000
  name:     "sec_touchscreen"
  location: "sec_touchscreen/input1"
  id:       ""
  version:  1.0.1
  events:
    KEY (0001): KEY_WAKEUP            BTN_TOOL_FINGER       BTN_TOUCH             01c7
                02be
    ABS (0003): ABS_X                 : value 0, min 0, max 4095, fuzz 0, flat 0, resolution 0
                ABS_Y                 : value 0, min 0, max 4095, fuzz 0, flat 0, resolution 0
                ABS_MT_SLOT           : value 0, min 0, max 9, fuzz 0, flat 0, resolution 0
                ABS_MT_TOUCH_MAJOR    : value 0, min 0, max 255, fuzz 0, flat 0, resolution 0
                ABS_MT_TOUCH_MINOR    : value 0, min 0, max 255, fuzz 0, flat 0, resolution 0
                ABS_MT_POSITION_X     : value 0, min 0, max 4095, fuzz 0, flat 0, resolution 0
                ABS_MT_POSITION_Y     : value 0, min 0, max 4095, fuzz 0, flat 0, resolution 0
                ABS_MT_TRACKING_ID    : value 0, min 0, max 65535, fuzz 0, flat 0, resolution 0
                003e                  : value 0, min 0, max -1, fuzz 0, flat 0, resolution 0
  input props:
    INPUT_PROP_DIRECT
```
touch_screen_max_x is 4095

touch_screen_max_y is 4095

## Record on android
To create an event_file.txt

1. Run `adb shell getevent -tl > event_file.txt`
2. Perform the actions that you want to record on your android device
3. Stop the recording with CTRL C
4. Generate the arduino sketch
    `python convert_to_code.py touch_screen_max_x touch_screen_max_y event_file.txt [optional_rounding_value=3]`
## Tips

Try to make as few actions as possible while recording

The attiny can not hold medium-large recorded scripts. Setting optional_rounding_value to 15+ may help in the event that your sketch is too large.
### set optional_rounding_value
   The default value is 3

   If the previous x or y is less than optional_rounding_value from the next recorded value the next recorded value will not be added to the arduino sketch.


