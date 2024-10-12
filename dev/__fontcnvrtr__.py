import contextlib
with contextlib.redirect_stdout(None):
    import pygame
    import numpy
from math import ceil
import pathlib
import os
from inspect import getsourcefile
from os.path import abspath
from time import sleep

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

class tarchar():
    """A voxel representation of the characaters"""
    def __init__(self,charbin : list[numpy.uint8],dx,dy):
        self.charbin = charbin    # a Uint8 where each bit represents wether the pixel is filled or not
        self.dx = dx
        self.dy = dy
    def printvisu(self):
        toreturn = "#"
        for p,op in enumerate(self.charbin):
            
            for p_i in range(8):
                if (p*8+p_i)%self.dx == 0:
                    toreturn += "#\n#"
                currentbin = (op >> p_i)%2
                if currentbin == 0:
                    toreturn += "##"
                else:
                    toreturn += "--"
        return toreturn

class fontsurf():
    def __init__(self,path:str):
        self.name :                  str = path[path.rfind("/"):path.rfind(".")]
        self.fontsurf :   pygame.Surface = pygame.surfarray.array2d(pygame.image.load(path))
        self.size :           tuple[int] = self.fontsurf.shape
        self.assigns : dict[int,tarchar] = dict()    # ASCII code -> Tarchar
        self.hpx :             list[int] = list()    # Historic of px on the raw image
        self.hpy :             list[int] = list()    # Same but for py
        self.hlid :            list[int] = list()    # Same but for ASCII codes assignements

    def __getdy(self,px: int ,py: int ) -> int:
        """Get dy of the character at position px;py"""
        dy = 0
        while True:
            if py+dy >= self.size[1]:
                return -1
            elif self.fontsurf[px][py+dy] == -65536:
                break
            elif dy > 9999:
                raise Exception("Couldn't find -65536 to get dy, bad png format")
            dy += 1
        return dy-1
    def __getdx(self,px: int ,py: int ) -> int:
        if not (self.fontsurf[px][py] == -16776961):
            raise Exception("the pixel at "+int(px)+";"+int(dy)+" is not a dx marker (of color rgb#FF0000)")
        sx = 0
        while self.fontsurf[px+sx][py] == -16776961:
            sx += 1
        return sx

    def __chartotarfont(self,px: int,py: int,dx: int,dy: int):
        a = list() # each bit represend a pixel, it's sort of a voxel array but 2d and for font
        toappend = numpy.uint8(0)
        for p in range(ceil(dx*dy/8)):
            toappend = numpy.uint8(0)
            for p_i in range(0,8):
                p_f = p*8+p_i
                if p_f < dx*dy: # make sur its not oob
                    tobitwop = numpy.uint8(self.fontsurf[px+p_f%dx][py+p_f//dx] != -1)<<p_i
                    toappend = toappend | tobitwop
            a.append(toappend)  # appends the uint8
        return tarchar(a,dx,dy)

    def assign(self,letterid:str,cchar : tarchar):
        mode = (len(letterid)==1)   # assigns the input to the voxel array
        try:
            if mode:                    # ASSIGNMENTS
                print("Assigning: "+letterid+" using classic protocol:\n"+str(ord(letterid))+" -> tarchar."+letterid)
                self.assigns[ord(letterid)] = cchar
                self.hlid.append(ord(letterid))
            else:
                print("Assigning: "+letterid+" using ASCII to UTF-8")
                chr(int(letterid))
                self.assigns[int(letterid)] = cchar
                self.hlid.append(int(letterid))
        except ValueError:
            #__delines(toprint.count("\n"))
            print(bcolors.FAIL+"[Error]"+bcolors.ENDC+": Could not convert "+letterid+" to a UTF-8 int32 representation")
            self.hpx.pop(-1)
            self.hpy.pop(-1)
            return False
        return True

    def __delines(self,dx):
        for dl in range(dx):
            print(tcmd.GO_UP+tcmd.CLEAR,end="")

    def getfontdict(self):
        """Get font as a dictionnary with key : pixel surfarray"""
        toreturn = dict()
        px = 0
        py = 0
        self.hpx = list()    # historique des px
        self.hpy = list()    # historique des py
        self.hlid = list()   # historique des assignements
        dy = 0
        dx = 0
        while True:
            dy = self.__getdy(px,0)
            if dy == -1:
                self.convert()
                break
            dx = self.__getdx(px,0)
            self.hpx.append(px)
            self.hpy.append(py)
            cchar = self._fontsurf__chartotarfont(px,1,dx,dy)
            toprint = cchar.printvisu()
            toprint = toprint[:dx*2+5] + " LETTER ASSIGNEMENT PROCESS :" + toprint[dx*2+5:dx*4+8] + " ============================"+toprint[dx*4+8:dx*6+11]+" Input what this letter is on your keyboard"+toprint[dx*6+11:dx*8+14]+" or its ASCII ID if you are unable to do so"+toprint[dx*8+14:dx*12+20]+" Type :b to reassign previous letter"+toprint[dx*12+20:dx*14+23]+" Type :qa to end process without saving"+toprint[dx*14+23:dx*16+26]+" Type :c to skip to conversion"+toprint[dx*16+26:]
            print(toprint)
            letterid = input(bcolors.OKGREEN+"[TARFNTmkr]"+bcolors.ENDC+":"+bcolors.OKCYAN+" Input letterid/letter"+bcolors.ENDC+": ")
            # ====== HISTORY FUNCTION ========
            if letterid == ":b":    # go back function
                self.hpx.pop(-1)
                self.hpy.pop(-1)
                py = self.hpx[-1]
                px = self.hpx[-1]
                self.hpx.pop(-1)
                self.hpy.pop(-1)
                del self.assigns[self.hlid[-1]]
                self.hlid.pop(-1)
                self.__delines(toprint.count("\n")+2)
                continue
            elif letterid == ":qa":
                return dict()
            elif letterid == ":c":
                self.convert()
                break
            #-------------------------
            self.__delines(toprint.count("\n")+2)
            success = self.assign(letterid,cchar)
            if success:
                px += dx+1                  # moves to the next letter


    def convert(self):
        print("\n==================================================================\n --- END OF ASSIGNEMENT : --- \n==================================================================\n"+bcolors.OKGREEN+"[Starting conversion]"+bcolors.ENDC+"...")
        outputpath = abspath(getsourcefile(lambda:0)).replace("__fontcnvrtr__.py","")+"tarfnt"+self.name+".trfnt"
        print("   Using location: "+outputpath)
        with open(outputpath,"bw+") as trfnt:
            for item in self.assigns.keys():
                ctarchar : tarchar = self.assigns[item]     # liste des assignements
                cdx = numpy.uint8(ctarchar.dx)              # equivalent byte de dx
                cdy = numpy.uint8(ctarchar.dy)              # equivalent byte de dy
                toconvert = numpy.uint8(item)               # equivalent byte de l'entrée
                print("      Adding entry for: "+hex(item)+"->",bin(toconvert),"with metadata:",bin(cdx),bin(cdy))
                trfnt.write(toconvert),trfnt.write(cdx),trfnt.write(cdy)    # ajoute une entrée au fichier
                charbinlen = len(ctarchar.charbin)                          # get la len du charbin pour le visuel
                print("this line is gonna get replaced so you wont get to see it unless your reading this code and if thats the case i love you please marry me")
                # ----------------------------------------------------------
                for i,byte in enumerate(ctarchar.charbin):
                    cpercent = str(int(round((i/charbinlen*100),0)))
                    termlen = os.get_terminal_size()
                    toprint = "     Writing: "+bin(byte)
                    termlen = termlen.columns-len(toprint)-32
                    intermediary = ceil(i/charbinlen*20)
                    toprint = toprint + termlen*" "+(cpercent)+(3-len(cpercent))*" "+"% ["+intermediary*"#"+(20-intermediary)*"-"+"]"
                    print(tcmd.GO_UP,tcmd.CLEAR,tcmd.CLEAR,toprint)
                    trfnt.write(byte)
        print(bcolors.OKGREEN+"[CONVERSION SUCCESS]"+bcolors.ENDC)
#==================================================================================
def launchconversion(inp : str):
    optindex = inp.find("'")
    if optindex == -1:
        print(bcolors.FAIL+"SyntaxError:"+bcolors.ENDC+" string malformation, could not process the argument as a string")
        return
    inp = inp[optindex:].replace("'","")
    try:
        currentfont = fontsurf(inp)
        print("""Launching process of conversion :\nBE AWARE THAT THIS PROCESS REQUIRE HUMAN INTERVENTION\n-----------------------------------------------------""")
    except Exception as err:
        print(bcolors.FAIL+"ConversionError:"+bcolors.ENDC+" could not process the file:\n",err)
        return
    currentfont.getfontdict()
