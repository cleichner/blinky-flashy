blinky-flashy
=============

Source code for the holiday party light display.

installation
============

1. Beg for samples.
2. Spend all of the time soldering.
3. pip install ino
4. ino build
5. plug in arduino
6. ino upload
7. Blinky-flashy party.

architecture
============
This is split into a main control module (src/sketch.ino) and libraries for
interaction with the high-level LED display (lib/Display/), the remote control
car (lib/Car/). It uses a library to interact with the low-level constant current
driver chip (lib/Tlc5940) as well as a software timer library to drive the
interface (lib/Timer).

logging
=======

If you make changes, uncomment `t.every(10, log)` and run
`ino serial -b 115200` to see the output.

bugs
====

Lots of them. This was written very quickly and is sparsely tested.

