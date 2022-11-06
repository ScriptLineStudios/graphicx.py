import time
import graphicx
import random

surf = graphicx.Surface((40, 20))
_ = 0
__ = 0
time = 0

y_vel = 1
x_vel = 1
while True:
    time += 1
    i = 0
    surf = graphicx.clear(surf)
    surf = graphicx.draw_rect(surf, (_, __, 2, 2), (255, 255, 255))

    
    if time %200 == 0:
        _ += x_vel
        __ += y_vel

    if _ > 35:
        x_vel = -1
        y_vel = random.choice([-1, 1])
        
    if _ < 1:
        x_vel = 1
        y_vel = random.choice([-1, 1])


    if __ > 17:
        y_vel = -1
        x_vel = random.choice([-1, 1])


    if __ < 1:
        y_vel = 1
        x_vel = random.choice([-1, 1])


    for y in range(20):
        for x in range(40):
            pos = (y * 40 + x)
            surf[pos]
            if surf[pos] != 1:
                print("#", end="")
            else:
                print("-", end="")
            i += 1
            if i % 40 == 0:
                print("")
                i = 0

    print("\033[H")
    
