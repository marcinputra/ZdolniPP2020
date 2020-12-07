import sys, pygame
width = 1000
height = 400

def interpPixels(lastpos,currpos):
    # Rysowanie kolek miedzy dwoma punktami
    xdiff = lastpos[0] - currpos[0]
    ydiff = lastpos[1] - currpos[1]
    for i in range(0,max(xdiff,ydiff)):
        pass



if __name__ == "__main__":
    pygame.init()
    pygame.display.init()
    # Ustawienia okna
    pygame.display.set_caption("Rysowanie")
    mainSurface = pygame.display.set_mode(size=(width,height), flags=pygame.RESIZABLE)
    mainSurface.fill(color=(255,255,255))
    pygame.display.flip()

    lastpos=(0,0)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit(0)
            # Mouse events
            #if event.type == pygame.MOUSEBUTTONDOWN:
            #  mpos = event.pos
            #  mbutton = event.button
            #  pygame.draw.circle(surface)
        ###if pygame.mouse.get_pressed()[0] == True:
            # Wcisniety jest lewy przycisk myszy
            
            mpos = pygame.mouse.get_pos() # Tuple (x, y)
            pygame.draw.circle(surface=mainSurface, color=(0,0,0), center=mpos, radius=1, width=1)
            if lastpos != mpos:
                #interpPixels(lastpos,mpos)
            lastpos = mpos
            pygame.display.update() # For debug only!
