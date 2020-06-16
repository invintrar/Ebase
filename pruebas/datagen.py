import sys
import time
import math
import random
tmax = float( sys.argv[1] )
t = 0
while 1:
    dt = tmax
    time.sleep(1)
    t += 1
    print t, math.sin(0.1*math.pi*t/tmax)