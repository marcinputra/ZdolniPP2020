import sys, pygame
import math
width = 1000
height = 400

def interpPixels(surface,lastpos,currpos):
    # Uzupelnianie kolek miedzy dwoma punktami
    xdiff = lastpos[0] - currpos[0]
    ydiff = lastpos[1] - currpos[1]
    highnum = max(abs(xdiff),abs(ydiff))
    if highnum == abs(xdiff):
        high = xdiff
        low = ydiff
    else:
        high = ydiff
        low = xdiff
    for i in range(0,highnum):
        
        pygame.draw.circle(surface=surface, color=(0,0,0), center=(xpos,ypos), radius=1, width=1)


if __name__ == "__main__":
    pygame.init()
    pygame.display.init()
    # Ustawienia okna
    pygame.display.set_caption("Rysowanie")
    mainSurface = pygame.display.set_mode(size=(width,height), flags=pygame.RESIZABLE)
    mainSurface.fill(color=(255,255,255))
    pygame.display.flip()

    lastpos=(0,0)
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
                lastpos = None

            if mouseDown == True:
                if event: mpos = event.pos
                pygame.draw.circle(surface=mainSurface, color=(0,0,0), center=mpos, radius=1, width=1)
                if lastpos is not None:
                    interpPixels(mainSurface, lastpos,mpos)
                lastpos = mpos
            pygame.display.update() # For debug only!
