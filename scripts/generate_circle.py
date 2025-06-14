import math

resolution = 10

theta = 0
for i in range(resolution - 1):
    theta += 360 / resolution

    alpha = 0
    for j in range(resolution - 1):
        alpha += 360 / resolution
        x = math.cos(math.radians(alpha)) * math.sin(math.radians(theta)) / 2
        y = math.sin(math.radians(alpha)) * math.sin(math.radians(theta)) / 3
        z = math.cos(math.radians(theta)) / 2
        
