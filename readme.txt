Simple and non-blocking Arduino module loader, configurable as a Marlin type firmware (3d printer firmware), and compatible with any Arduino, I run it on an Arduino nano
created for my personal use without pretension, but it can be used by others, some modules are not finished. 
the main one is the management of the modules when it is finished in the very first version, of course to optimize

If you followed the same principle, you could add any module without modifying the base
this one was coupled to a raspberry pi zero to have total control over the firmware live from the network

The build file is intended to be installed on linux, raspberry
The firmware is compiled on it and pushed to the arduino
all this from the network

these are a project dedicated to people skilled in the field of coding, and not intended for the general public ( because I will not provide more information about the operation, experts will simply understand )
More information on the modules present later, but you do not want to use my modules

The latest update was to replace all malloc for better memory management, because my arduino is full of crackers although there was no memory leak
But ultimately, it didn't change anything on the amount of memory available during operation, but anyway the code is cleaner like that

Tips: use static relays to avoid noise when triggering
Tips2: use isolated power supply or encapsulated DC-DC to avoid external interference
