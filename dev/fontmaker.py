import contextlib
with contextlib.redirect_stdout(None):
    import pygame
    import numpy
from math import ceil
import pathlib
import __fontcnvrtr__

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class tcmd:
    GO_UP = "\033[1A"
    CLEAR = "\x1b[2K"

def launchloop():
    running = True
    while running:
        inp = input(bcolors.OKGREEN+"[TARFNTmkr]"+bcolors.ENDC+"$ ").replace("\"","'")
        if inp == "help":
            print("""-------------------------------------------------------------------------\nTARFNTmkr user manual :
                  \nconvertfont %folder%    #converts a .png prepared file into a TARFNT""")
        if inp == "exit" or inp == "quit":
            running = False

# ==============================================================
        if "convertfont" in inp:
            __fontcnvrtr__.launchconversion(inp)

if __name__ == "__main__":
    launchloop()
