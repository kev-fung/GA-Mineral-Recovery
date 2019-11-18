# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 10:27:49 2019

@author: karad
"""


import numpy as np
#import sys
import graphviz
from graphviz import Graph


N=20 # Number of files



for i in range(1, N):

    

    graph = graphviz.Digraph(format='jpg')
    
    #read vectors in file
    vec = np.loadtxt("best_vectors_%d.txt"%(i*100), dtype = int) #a[i]#[0,1,2,4,3,1,5,4,0] #[int(_) for _ in sys.argv[2:]]
    
    
    N = (len(vec)-1)//2
    
    def label(x):
        if x<N:
            return 'Unit %s'%(x)
        elif x==N:
            return 'Tailings'
        else:
            return 'Concentrate'
    
    graph.attr(rankdir='LR')
    graph.attr('node', shape='rectangle')
    
    graph.edge('Feed', label(vec[0]), color='blue',
               headport='w', tailport='e', dir='forward')
    
    #G,pos,nodelist=COLORS.keys(),cmap=plt.get_cmap(cmap), node_size=nodesize,alpha=.6,vmax=1,vmin=0, node_color = COLORS.values()
    #pos=graph.graphviz_layout()
    
    for _ in range(N):
        graph.edge(label(_), label(vec[2*_+2]), color='blue',
                   headport='w', tailport='n',
                   dir='forward')
        graph.edge(label(_), label(vec[2*_+1]), color='red',
                   headport='w', tailport='s',
                   dir='forward')
    
    with graph.subgraph() as s:
        s.attr(rank = 'source')
        for n in ('Feed',):
            s.node(n)
    
    with graph.subgraph() as s:
        s.attr(rank = 'sink')
        for n in ('Tailings', 'Concentrate'):
            s.node(n)
    
    graph.attr(label="vector: %s"%vec)
    graph.render(filename="iteration_%d"%i, cleanup=True)
    #graph.close()
