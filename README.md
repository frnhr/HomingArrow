# HomingArrow 1.0.1

Hardware arrow that points to a GPS coordinates.


## Pre-configuration

Pre-configuration includes parameters that can be changed in the Arduino code. This in turn means that Arduino needs to be flashed (burned, uploaded...) with the new code every time a pre-configuration parameter is changes.

Naturally, pre-configuration parameters are such that they rarely (if ever) need to be changed.


### Pre-configuration vs EEPROM Configuration

Parameters that change during normal operation of the device are stored in Arduino EEPROM, and are accessible via Serial interface. More details below.


### List of Pre-configuration Parameters


###### Parameter `COMPASS_MAGNETIC_DECLINATION`

Fixed angle between magnetic and geographic north pole. This angle greatly varies for different areas on Earth. To find out your local magnetic declination, visit [magnetic-declination.com] [1] 


###### Parameter `MOTOR_DEADZONE`

Arrow error angle that is acceptable, i.e. that won't trigger arrow movement. Theoretical limit for the deadzone is:

    MOTOR_DEADZONE = 360 / ENCODER_RESOLUTION / 2

This gives a half a minimal resolution angle on either side of a position, adding up to full minimal resolution angle.

Default value is:

    MOTOR_DEADZONE = 360 / ENCODER_RESOLUTION / 2 * 1.1

The `1.1` multiplier gives a small overlap (10%) between adjacent position, preventing arrow to go back and forth if it is on the edge between two positions.

If arrow is still observed to move back and forth in minimal movements, then increase this parameter. Increasing the 1.1 multiplier a fraction (to 1.2) might be enough.


###### Parameter `MOTOR_MIN_SPEED`

Speed is proportional to the arrow error angle (while inside angle defined in `MOTOR_SLOWZONE`). 
`MOTOR_MIN_SPEED` controls starting speed of the motor.
If motor is observed to stall when it should have moved the arrow for a very small angle, then try increasing `MOTOR_MIN_SPEED` parameter by 5 or 10.


###### Misc

There are many additional parameters in the `/***** Configuration *****/` in `.h` files of most modules.
They define things like pins used by the module, hardware-specific constants, EEPROM addresses, etc.


## Blink Patterns

Arduino Nano (and most of other Arduino board as well) have a build-in LED on pin 13. We are using this LED to report status of the device.

    Setup:       BBBB____BBBB____BBBB____BBBB____BBBB____  
    Idle:        B___________________B__________________
    Low battery: BBB___BBB___B______BBB___BBB___B______
    No GPS fix:  B__B__B__B__B__B__B__B__B__B__B__B__B__

`BBBB` represents a 1-second blink interval, other intervals are only roughly to scale.
For exact values, see `BLINK_SETUP` and other in `blink.h`.


## Serial Protocol

Commands to Arduino are on sent on single line.
The complete list of available commands is given below.

Responses can be success or error. Both follow the same format:

    ok N
    line 1
    line 2
    ...
    line N


Similarly for errors:

    error N
    line 1
    line 2
    ...
    line N

... where `N` is the number of additional lines in the response. 
Can be `0` or more. 

It is the responsibility of the the master (device that issued the command) to read these two lines and act on them if needed.

###### Examples:

**Successful command with 2 lines of additional data**:

	[SEND] set_target 12.3,13.4

	ok 2
	12.30000019
	13.40000057

The `set_target` command always returns the values that are actually in the Controller memory. Because of floating point arithmetic and the way floating point numbers are stores, the final values sometimes can be slightly different from the values given in the command.


**Unsuccessful command**:

	[SEND] make_me_a_coffie now

	error 2
	Unknown command
	make_me_a_coffie now

This response also returns two lines of additional data. First line explains the error, and second line returns the command that was given to the Controller. This can be used for troubleshooting (e.g. if there is interference on the serial line, some characters will be transmitted wrongly).

> NOTE: `2` in `error 2` is **not** an error code!


### Available Commands

These commands are implemented in `serial.ino`.


Command (single line)            | Response | Additional data & Description
---------------------------------|----------|--------------------------------------------------------------
ping                             | ok 2     | Device name and version.
status                           | ok 13    | Many aspects of the device operation, see below.
set_target N                     | ok 2     | Sets target to North, useful for troubleshooting.
set_target S                     | ok 2     | Sets target to South, useful for troubleshooting.
set_target 12.3456768,23.4567890 | ok 2     | Set target to provided coordinates, see below for details.
set_zone 3.5                     | ok 1     | Sets target zone to provided number of **meters**.
set_offset 23                    | ok 1     | Sets offset for the arrow pointer to the provided angle (degrees). This is useful if hardware structure requires components to be put in non-parallel orientation.


#### Command `status`

This command reports status of the device. Response is somewhat verbose, containing 13 lines of data.

Example response:

    ok 13
    current_lat: 0.12345678
    current_lon: 1.23456789
    target_lat: 12.34566789
    target_lon: 13.45678901
    distance: 1231231.2
    gps_fix: True
    delta_az: 0.7
    hardware_offset: 332.0
    on_target: False
    target_zone: 10.0
    magnetic_declination: 0.00
    battery_v: 8.38
    battery_low: False

Data items explained:

value           | explanation
----------------|------------------------------------------------------------------
current_lat     | Latitude of current location, read from GPS module.
current_lon     | Longitude of current location, read from GPS module.
target_lat      | Latitude of target location, set using `set_target` command.
target_lon      | Longitude of target location, set using `set_target` command.
distance        | Distance from current location to target location. Not accurate for large distances (hundreds of kilometers) because it ignores Earth curvature.
gps_fix         | Whether GPS module has a fix. If a fix is lost, the device will continue to operate with previously acquired position.
delta_az        | Difference between azimuth to target and azimuth pointed by the arrow. Related to `MOTOR_DEADZONE` parameter.
hardware_offset | Arrow offset, might be required due to hardware implementation of the arrow and encoder - motor transmission.
on_target       | "True" if current position within target zone around target position. "False" otherwise.
target_zone     | Radius around target position that is considered to be "on target".
magnetic_declination | Value of `COMPASS_MAGNETIC_DECLINATION` parameter.
battery_v       | Voltage of external power supply. Note that this will be off when device is powered via USB.
batter_low      | "True" if battery voltage below 7.5 V, "False" otherwise. Note that this will be off when device is powered via USB.


#### Command `set_target`

Parameters for this command are latitude and longitude, separated by a comma, and optionally a space as well.

Good:

    set_target 12.3456,23.45687
    set_target 12,23
    set_target 12.3456, 23.45687
    set_target 12, 23

Bad:

    set_target 12.3456 23.45687
    set_target 12 23
    set_target12.3456,23.45687

A handy way to get GPS coordinates is using [itouchmap.com] [3] web site.

There are two special parameters:

    set_target N
    set_target S
    
These two parameters (`N` and `S`) set coordinates to North and South pole, respectively, useful for troubleshooting.
They are equivalent to specifying coordinates manually (e.g. `90,0` for `N`).


## Code and Naming Conventions

This projects strives to be compliant with guidelines that are spelled out in this section. However, complete compliance is not claimed.

### Project Structure

Code structure is somewhat uncommon for an Arduino "sketch".
Reason for this is the objective to keep different logical elements (known as "**modules**") separately and with strictly defined interfaces between them.
This keeps code clean and easy to understand, as well as potentially reusable in other projects.

Each module has either an `.ino` or a `.h` file, or both. They are named the same, using lowercase and underscore-separated words (e.g. `my_module.ino` and `my_module.h`).

Main module, the sketch that runs other modules, is named `HomingArrow.ino` (it also has the corresponding `.h` file). UpperCamelCase in filename is used to distinguish it from other modules.

>  Note that ArduinoIDE requires that main module (a.k.a. "**sketch**") file be located in a folder with the same name. 
>      
>    --------
>    
>    Good: `HomingArrow/HomingArrow.ino`  
>    Bad: `code_for_the_arduino/HomingArrow.ino`  
>    
>    --------  
>    
>    This is not required by avrdude (the firmware uploader used by ArduinoIDE) and it certainly is not a C++ requirement. Moreover, some alternative IDEs such as Stino / Sublime Text don't have that restriction. It seems to be an arbitrary restriction, imposed decision by ArduinoIDE for no good apparent reason.


### Module Structure


#### Functions

Most modules provide two functions:

 * `void my_module_setup()`
 * `void my_module_loop()`

These functions are expected to be called from `void setup()` and `void loop()` respectively.

Some module loop functions should be throttled (i.e. called **not**-as-ofter-as-possible).
Main `loop()` is expected to handle that, i.e. no internal time tracking is done by modules in this regard.

Additional functions can be provided by the module as required.

**Convention:** All functions should start with module name, e.g. `my_module_foo()`.  

**Convention:** Function that are meant to be private to the module should start with underscore and the module name, e.g. `_my_module_bar()`.  


#### Configuration Constants

All configuration constants, specified with `#define` preprocessor command, should begin with uppercase module name, e.g. `#define MY_MODULE_BAZ_PIN 123`.


#### Interfaces

Most modules define a public and a private struct that holds all variables used by that module.
This is for convenience, and to reduce usage of global namespace.
And example struct might look like this:
    
	struct {
	    int foo = 123;       // description of foo
	    String bar = 45.67;  // description of bar
	} my_module;

**Public** interface struct should be named the same as modules (e.g. `my_module`). 

**Private** struct name should start with an underscore and module name (e.g. `_my_module`).


###### Calling Module Functions

As a rule, modules should never call each others' functions.
Instead, all function calling should be done from module's `loop` (that is in turn called by the main `loop()`).

Module should expose variables in its public struct.
All external input should be handled via those variables.

This helps to control call stack depth. In doing so we are keeping more SRAM available for variables and normal usage. 
For more detail, see [this tutorial on adafruit.com] [2].


#### Why no Classes?

Usage of structs and naming convention is a compromise between simplicity and using C++ features "the right way". 
Technically, a better choice would have been to use classes.
However, this approach is deemed a good compromise in order to make the code more understandable to readers without C++ background.



[1]: http://www.magnetic-declination.com/ "magnetic-declination.com"
[2]: https://learn.adafruit.com/memories-of-an-arduino/ "Memories of an Arduino, a tutorial by Adafruit"
[3]: http://itouchmap.com/latlong.html "Online tool on itouchmap.com"
