# DisplayCore

The DisplayCore system builds on the popular TFT library to create
a fully modular and easily expandable video display system for chipKIT
boards.

Instead of just one huge monolithic library the DisplayCore system is split
into a number of much smaller libraries, each one handling a specific task.
Each display has its own dedicated library, as do the different touch input
systems.  The idea of an abstracted connector system has been dropped in favour
of embedding the connectivity into the screen driver.

All this means:

* Smaller code - you only include the parts you need
* Faster compilation - you don't need to compile code you won't be using
* Faster display access - removing the communication abstraction layer makes communication much faster
* Easy to support more displays - not just TFT screens, but any display technology can now be supported
