# alkylFW
Alkylation development framework:
A lightweight 2D platform independant portable graphics rendering library with integrated software development librairies
Based on the KISS (Keep It Stupid Simple) principle, standard features only include basic rendering utilities, Pixmaps and TrueType fonts rendering.

Staff:
* Project header & developper : yuipercent
* Developper : Loli Lambda

## git structure :
### ./
* alkylfw.h : Main header for the library which includes all standard features
* tester.c  : some random tester files used for testing if all of this works

### /core :
* alkclib.h : Contains features which permit platform independency ( compatibility macros )
* alkore    : Core features of the library such as structures, initializer etc...
* eventlib  : Event manager library essentially, the interface between OS-specific events and Alkyl events

### /plug :
* naphtools : Features of the standard library such as napht blitting, rectangle filling etc...
* alkorext  : napht derivatives library

### /srclib :
* alkc_x11  : X11 compatibility library
* alkc_windows : Windows compatiblity library

### /dev :
random stuff
