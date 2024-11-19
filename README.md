# alkylFW
**/!\ THIS IS A WORK IN PROGRESS, UNTIL A RELEASE IS PUBLISHED YOU WILL NOT BE ABLE TO MAKE THIS WORK**

Alkylation development framework:
A lightweight 2D platform independant portable graphics rendering library with integrated software development librairies.
Based on the KISS (Keep It Stupid Simple) principle, standard features only include basic rendering utilities, Pixmaps and TrueType fonts rendering, essentially a low amount of highly polyvalent features.

Prioritizes speed over memory efficiency, currently not suited for embedded system

### Planned:
* Embedded systems lightweight memory-efficient librairies
* OpenType font support
* Python / Rust / C# API
* GPU acceleration (SIMD for CPU already implemented)

Staff:
* Project header & developper : yuipercent
* Developper : Loli Lambda

## git structure :
### ./
* alkylfw.h : Main header for the library which includes all standard features, essentially brings together all the other files
* tester.c  : some random tester files used for testing if all of this works

### /core :
* alkclib.h : Contains features which permit platform independency ( compatibility macros )
* alkore    : Core features of the library such as structures, initializer etc...
* eventlib  : Event manager library essentially, the interface between OS-specific events and Alkyl events

### /plug :
* naphtools : Features of the standard library such as napht blitting, rectangle filling etc...
* naphtfont : Font rendering standard plugin
* alkorext  : napht derivatives library

### /srclib :
* alkc_x11  : X11 compatibility library
* alkc_windows : Windows compatiblity library

### /dev :
random stuff (soon to be deleted)
