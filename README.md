# HomingArrow 0.9.0

Hardware arrow that points to a GPS coordiantes.


## Pre-configuration

Preconfiguration includes parameters that can be changed in the Arduino code. This in turn means that Arduino needs to be flashed (burned, uploaded...) with the new code every time a pre-configuration parameter is changes.

Naturally, pre-configuration parameters are such that they rarly (if ever) need to be changed.


### Pre-configuration vs EEPROM configuration

Parameters that change during normal oprtation of the device are stored in Arduino EEPROM, and are accessible via Serial interface. More details below.


### List of pre-configuration parameters

###### Magnetic declination

Fixed angle between magnetic and geographic morth pole. This angle greatly varies for different areas on Earth. To find out your local magnetic declination, visit [magnetic-declination.com] [1] 

###### Misc

There are many additional paramters in the "/***** Configuration *****/" in `.h` files of most modules.
They define things like pins used by the module, hardware-specific constants, EEPROM addresses, etc.


## Code and naming conventions


### Project structure

Code structures is somewhat uncommon for an Arduino "sketch".
Reason for this is that different logical elements (known as "**modules**") are keps separatly and with strictly defined interfaces between them.
This keeps code clean and easy to understand, and reusable.

Each module has either an `.ino` or a `.h` file, or both. Then are named the same, using lowercase and underscore-separated words (e.g. `my_module.ino`).

Main module, the sketch that runs other modules, is named `HomingArrow.ino` (it also has the corresponding `.h` file). UpperCamelCase in filename is used to distinguish it from other modules.

Note that ArduinoIDE requires that main module (a.k.a. "**sketch**") file is located in a filder with the same name. This is not required by avrdude (and alternatice IDEs such as Stino / Sublime Text), but a sole quirk of ArduinoIDE.


### Module structure


#### Functions

Most modules provide two functions:

 * `void my_module_setup()`
 * `void my_module_loop()`

 These two functions are expected to be called from `void setup()` and `void loop()` respectively.
 Some module loop functions should be throttled (run **not**-as-ofter-as-possible).
 Main `loop()` is expected to handle that, i.e. no internal time tracking is done by module in this regard.

Additional function can be provided by the module as required.

**Convention:** All functions should start with module name, e.g. `my_module_foo()`.

**Convention:** Function that are meant to be private to the module should start with underscore and the module name, e.g. `_my_module_bar()`.


#### Configuration constants

All configuration constants, specified with `#define` preprocessor command, should begin with uppercase module name, e.g. `#define MY_MODULE_BAZ_PIN 123`.


#### Interfaces

Most modules define a public and a private struct that holds all variables used by that module.
This is for convenicence, and to reduce usage of gobal namespace.
And example struct might look like this:
    
	struct {
	    int foo = 123;       // description of foo
	    String bar = 45.67;  // description of bar
	} my_module;

**Public** interface struct should be named the same as modules (e.g. `my_module`). 

**Private** struct name should start with an underscore and module name (e.g. `_my_module`).


###### Calling module functions

As a rule, modules should never call each others' functions.
Instead, all function calling should be done from module's `loop` (that is in turn called by the main `loop()`).

Module should expose variables in its public struct.
All external input should be handled via those variables.

This goes towards reducing call stack, keeping more SRAM available for variables and normal usage. 
For more detail, see [this tutorial on adafruit.com] [2].


#### Classes?

Usage of structs and naming convention is a compromise between simplicity and C++ features. 
Technically, a better choice would be to use classes.
However, target audience for most Arduino code is not familiar with advances aspects of C++ language.



[1]: http://www.magnetic-declination.com/ "magnetic-declination.com"
[2]: https://learn.adafruit.com/memories-of-an-arduino/ "Memories of an Arduino, a tutorial by Adafruit"
