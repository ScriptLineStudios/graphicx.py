import graphicx
import pygame

display = pygame.display.set_mode((600, 600))
clock = pygame.time.Clock()

surf = graphicx.Surface((600,600))
x = 0
while True: 
    surf = graphicx.clear(surf)

    surf = graphicx.draw_rect(surf, (x%600, 0, 40, 100), (255, 1, 255))
    x += 1
    s = pygame.image.frombytes(surf, (600, 600), "RGB")
    display.blit(pygame.transform.scale(s, (600, 600)), (0, 0))
    pygame.display.update()
    clock.tick()
    pygame.display.set_caption(f"{clock.get_fps()}")

