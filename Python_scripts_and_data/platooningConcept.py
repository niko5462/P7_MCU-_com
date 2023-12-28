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
    d += (PC1 := flow.Box(xy=(0, 0.1), w=2, h=1, label="Platooning\ncar1")).anchor(anchor='center').linewidth(3)
    d += (PC2 := flow.Box(xy=(-3, 0), w=2, h=1, label="Platooning\ncar2")).anchor(anchor='center').linewidth(3)
    d += (LC := flow.Box(xy=(3, -0.5), w=2, h=1, label="Leading\ncar")).anchor(anchor="center").linewidth(3)

    # subboxes

    #lines and arrows
    d += flow.Line().linewidth(4).linestyle(':').at(PC2.NW+0.3).tox(LC.NE)
    d += flow.Line().linewidth(4).linestyle('--').at(PC2.SW-0.8).tox(LC.SE)
    d += flow.Line().linestyle(':').at(PC1.E).to(LC.NW)
    d += flow.Line().linestyle(':').at(PC1.E).to(LC.SW)
    d += flow.Line().linestyle(':').at(PC2.E).to(PC1.NW)
    d += flow.Line().linestyle(':').at(PC2.E).to(PC1.SW)
    # d += flow.Line().linestyle('-').at(ESP.N).toy(ToF.S-0.2).label('b', loc='bottom', ofst=(.3, -.1))

    # d += flow.Arc2(k=-.15,arrow ='-') \
    #     .at(ESP.N, dx=np.cos(70/180*np.pi), dy=np.sin(70/180*np.pi)) \
    #     .to(ESP.N, dy=1) \
    #     .color('Red'). label('A')
    # d += flow.Arc2(k=-.35,arrow ='-') \
    #     .at(ESP.N, dx=np.cos(70/180*np.pi)*0.75, dy=np.sin(70/180*np.pi)*0.75) \
    #     .to(ESP.N, dx=np.cos(110/180*np.pi)*0.75, dy=np.sin(110/180*np.pi)*0.75) \
    #     .color('blue').label('B', loc='bottom', ofst=(0.4,-0.2))
