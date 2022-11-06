import pygame
import graphicx
import matplotlib.pyplot as plt

class GraphicxEnv:
    def __init__(self):
        self.display = pygame.display.set_mode((600, 600))
        self.clock = pygame.time.Clock()

        self.surf = graphicx.Surface((600,600))
        self.prev_surf = None
        self.s = None
    def render_batch(self, size):
        framerate = 0

        for i in range(100):
            self.surf = graphicx.clear(self.surf)

            for i in range(size):
                 self.surf = graphicx.draw_rect(self.surf, (0, 0, 40, 100), (255, 1, 255))


            self.s = pygame.image.frombuffer(self.surf, (600, 600), "RGB")
            self.display.blit(self.s, (0, 0))
            pygame.display.update()
            self.clock.tick()
            framerate += self.clock.get_fps()
            self.prev_surf = self.surf

        return framerate / 100
    
class PygameEnv:
    def __init__(self):
        self.display = pygame.display.set_mode((600, 600))
        self.clock = pygame.time.Clock()

    def render_batch(self, size):
        framerate = 0

        for i in range(100):
            self.display.fill((0, 0, 0))

            for i in range(size):
                pygame.draw.rect(self.display, (255, 1, 255), (0, 0, 40, 100))
            
            pygame.display.update()
            self.clock.tick()
            framerate += self.clock.get_fps()

        return framerate / 100

pg_env = PygameEnv()
graphicx_env = GraphicxEnv()

x_axis = []

pg_fps = []
spark_fps = []
legend = False
plt.title("Drawing Various Amounts Of Rects")
for size in range(1000, 14000, 1):
    spark_fps.append(graphicx_env.render_batch(size))
    pg_fps.append(pg_env.render_batch(size))
    print(f"GRAPHICX = {spark_fps[-1]} PYGAME = {pg_fps[-1]}")

    x_axis.append(size)

    plt.plot(x_axis, pg_fps, label = "Pygame", color="green")
    plt.plot(x_axis, spark_fps, label = "Pygame + Graphix", color="black")
    if not legend:
        plt.legend()
        legend = True
    plt.pause(0.0001) #Note this correction
plt.show()

