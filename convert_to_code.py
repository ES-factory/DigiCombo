import os
import sys
# to create an input file for this script use "adb shell getevent -tl > recorded_events.txt"
# Then create your arduino code like this python .\tosend.py .\recorded_events.txt


def find_between(s, first, last):
    try:
        start = s.index(first) + len(first)
        end = s.index(last, start)
        return s[start:end]
    except ValueError:
        return ""


def print_help():
    print(
        "EXAMPLE USAGE: python convert_to_code.py touch_screen_max_x touch_screen_max_y event_file.txt [optional_rounding_value=3]\n\n")
    print("To determine touch_screen_max_x and touch_screen_max_y")
    print("    run 'run adb shell getevent -il'")
    print("        find an input device that looks like a touchscreen ie 'sec_touchscreen' beware you may have a touchpad which is not wanted")
    print("    ABS_MT_POSITION_X max is touch_screen_max_x")
    print("    ABS_MT_POSITION_Y max is touch_screen_max_y")
    print("example:")
    example = """            add device 12: /dev/input/event4
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
                INPUT_PROP_DIRECT"""
    print(example)
    print("\n\nTo create a event_file.txt")
    print("    run 'adb shell getevent -tl > event_file.txt'")
    print("    perform the actions that you want to record on your android device")
    print("    stop the recording with CTRL C")
    print("\n\noptional_rounding_value")
    print("   default value is 3")
    print("   recording events can create alot of events which tends to be hard to store in the attiny memory")
    print("   if the previous x or y is less than optional_rounding_value from the next recorded value the next recorded value will not be added")


if (len(sys.argv) < 4):
    print_help()
    exit(-1)
rounding_value = 3
if (len(sys.argv) == 5):
    rounding_value = int(sys.argv[4])
touch_screen_max_x = int(os.path.basename(sys.argv[1]))
touch_screen_max_y = int(os.path.basename(sys.argv[2]))
input_file_name = sys.argv[3]

input_file = open(input_file_name, "r")

filename = os.path.splitext(os.path.basename(input_file_name))[0]
outfile = filename + "_DigiCombo.ino"

# Output file
fw = open(outfile, "w")
fw.write(
    "#include <DigiCombo.h>\n\nvoid setup() {\n  DigiCombo.begin();\n}\n\nvoid loop() {\n")
x = None
y = None
previous_x = None
previous_y = None
previous_time = None
# reduce mini drags if previous coordinates are within rounding_value do not add drag


def get_time_from_line(input_line):
    return int(find_between(
        input_line, "[", "]").strip().replace(".", "")[:-3])


for input_line in input_file.readlines():
    if not input_line.startswith("["):
        continue
    if previous_time == None:
        previous_time = get_time_from_line(input_line)
    part2 = input_line.split()
    ev_type = part2[3]
    event_name = part2[4]
    value = 0
    if (part2[5] == "DOWN"):
        value = part2[5]
    elif (part2[5] == "UP"):
        value = part2[5]
    else:
        value = int(part2[5], 16)
    if (event_name == "ABS_MT_POSITION_X"):
        x = value
    if (event_name == "ABS_MT_POSITION_Y"):
        y = value
    if (event_name == "BTN_TOOL_FINGER" and value == "DOWN"):
        fw.write("//Starting drag\n")
    if (x != None and y != None):
        if previous_x == None or previous_y == None or (rounding_value < abs(previous_x-x) or rounding_value < abs(previous_y-y)):
            current_time = get_time_from_line(input_line)
            fw.write(f"  DigiCombo.delay({current_time-previous_time});\n")
            fw.write(
                f"  DigiCombo.moveFinger({int((x/touch_screen_max_x)*10000)},{int((y/touch_screen_max_x)*10000)});\n")
            previous_time = current_time
        previous_x = x
        previous_y = y
    if (event_name == "BTN_TOOL_FINGER" and value == "UP"):
        fw.write("  DigiCombo.release();\n")
        fw.write("//Starting drag done\n\n")
        x = None
        y = None
        previous_x = None
        previous_y = None
        previous_time = None

fw.write("}")
print("Arduino sketch saved to " + outfile)
input_file.close()
fw.close()
