import sys, pygame
import math
import random
dimensions = (1000,400)

class vec2d:
    def __init__(self, x=0,y=0):
        self.x = x
        self.y = y
    def __sub__(self, other):
        return vec2d(self.x - other.x, self.y - other.y) # Operator odejmowania
    def __add__(self, other):
        return vec2d(self.x - other.x, self.y - other.y) # Operator dodawania
    def getMaxCoord(self, absolute=False):
        if absolute == False:
            return max(self.x,self.y)
        else:
            return max(abs(self.x),abs(self.y))

def interpPixels(surface,lastpos,currpos):
    # Uzupelnianie kolek miedzy dwoma punktami
    posdiff = lastpos - currpos
    highnum = posdiff.getMaxCoord(absolute=True)
    updatelist = []
    for i in range(highnum):
        x = int(currpos.x + (float(i)/highnum * posdiff.x))
        y = int(currpos.y + (float(i)/highnum * posdiff.y))
        
        updatelist.append(pygame.draw.circle(surface=surface, color=draw_color, center=(x,y), radius=1, width=1)) # Narysuj i dodaj do listy do odswiezenia
    pygame.display.update(updatelist)


if __name__ == "__main__":
    pygame.init()
    pygame.display.init()
    # Ustawienia okna
    pygame.display.set_caption("Rysowanie")
    mainSurface = pygame.display.set_mode(size=dimensions)
    mainSurface.fill(color=(255,255,255))
    pygame.display.flip()

    draw_color=(0,0,0)
    lastpos=None
    mouseDown = False
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit(0)
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouseDown = True
            elif event.type == pygame.MOUSEBUTTONUP:
                mouseDown = False
                lastpos=None
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_e:
                    print("press")
                if event.key == pygame.K_f:
                    random.seed()
                    draw_color = (random.randint(0,255), random.randint(0,255), random.randint(0,255))
                    print("zmiana koloru na {}".format(draw_color))
                    

        if mouseDown == True and pygame.mouse.get_focused():
            mpos = pygame.mouse.get_pos()
            pygame.display.update(pygame.draw.circle(surface=mainSurface, color=draw_color, center=mpos, radius=1, width=1))
            if lastpos is not None and lastpos != mpos:
                interpPixels(mainSurface, vec2d(lastpos[0],lastpos[1]),vec2d(mpos[0],mpos[1]))
            lastpos = mpos
        if not pygame.mouse.get_focused(): lastpos = None # Resetuj ostatnia pozycje jezeli myszka wyjdzie po za okno

            
