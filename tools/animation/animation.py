# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 08:54:58 2019

@author: karad
"""

import imageio

N_files = 11 #number of files to read
filenames = [];
for i in range(1, 11):
    filenames.append("iteration_%d.jpg"%(i))

#kargs = { 'duration': 5 }
with imageio.get_writer('animation_circuit.gif', mode='I') as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)