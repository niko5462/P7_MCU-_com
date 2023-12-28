import matplotlib
import schemdraw.elements as elm
import numpy as np
import schemdraw
from schemdraw import flow


import os

matplotlib.use('Agg')

matplotlib.rcParams['font.serif'] = 'Palatino Linotype'
matplotlib.rcParams['font.family'] = 'serif'
matplotlib.rcParams['text.usetex'] = True

file = (os.path.basename(__file__)).replace(".py", "")
filepath = os.path.dirname(__file__) + '/'

with schemdraw.Drawing(file=(filepath + file + ".pdf")) as d:
    d.config(fontsize=10, unit=0.5)

    # main boxes
    d += (ESP := flow.Box(xy=(0, 0), w=2, h=4, label="Platooning\ncar")).anchor(anchor='center').linewidth(3)
    d += (ToF := flow.Box(xy=(1, 7), w=2, h=4, label="Leading\ncar")).anchor(anchor="center").linewidth(3)

    # subboxes

    #lines and arrows
    d += flow.Line().linewidth(4).linestyle(':').at(ESP.SW-0.2).toy(ToF.N)
    d += flow.Line().linewidth(4).linestyle('--').at(ToF.NE+0.2).toy(ESP.S)
    # d += flow.Line().linestyle(':').at(ESP.N).to(ToF.S,dx=-2,dy=-0.2)
    # d += flow.Line().linestyle(':').tox(ToF.S). label('a', loc='bottom', ofst=(0.5, 0))
    # d += flow.Line().linestyle(':').at(ESP.N).to(ToF.S, dy=-0.2). label('c',loc='bottom')
    # d += flow.Line().linestyle('-').at(ESP.N).toy(ToF.S-0.2).label('b', loc='bottom', ofst=(.3, -.1))

    # d += flow.Arc2(k=-.15,arrow ='-') \
    #     .at(ESP.N, dx=np.cos(70/180*np.pi), dy=np.sin(70/180*np.pi)) \
    #     .to(ESP.N, dy=1) \
    #     .color('Red'). label('A')
    # d += flow.Arc2(k=-.35,arrow ='-') \
    #     .at(ESP.N, dx=np.cos(70/180*np.pi)*0.75, dy=np.sin(70/180*np.pi)*0.75) \
    #     .to(ESP.N, dx=np.cos(110/180*np.pi)*0.75, dy=np.sin(110/180*np.pi)*0.75) \
    #     .color('blue').label('B', loc='bottom', ofst=(0.4,-0.2))
