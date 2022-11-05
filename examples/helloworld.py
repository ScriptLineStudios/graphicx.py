import graphicx
import pygame

display = pygame.display.set_mode((600, 600))
clock = pygame.time.Clock()

surf = graphicx.Surface((10,10))
#surf = pygame.Surface((600, 600))
while True: 
    surf = graphicx.clear(surf)
    for i in range(10000):
        #pygame.draw.rect(surf, (255, 255, 255), (0, 0, 60, 80))
        surf = graphicx.draw_rect(surf, (0, 0, 4, 4), (255, 255, 255))
        #surf = graphicx.test(surf)

    
    s = pygame.image.frombytes(surf, (10, 10), "RGB")
    display.blit(pygame.transform.scale(s, (600, 600)), (0, 0))
    pygame.display.update()
    clock.tick()
    pygame.display.set_caption(f"{clock.get_fps()}")

