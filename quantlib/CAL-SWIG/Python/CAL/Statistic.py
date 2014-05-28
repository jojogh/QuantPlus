# -*- coding: utf-8 -*-
'''
Created on Mar 28, 2014

@author: root
'''

from CAL import MersenneTwisterUniformRsg, MersenneTwisterUniformRng
from CAL import KnuthUniformRng, KnuthUniformRsg
from CAL import SobolRsg
from CAL import MoroInvCumulativeMersenneTwisterGaussianRsg
from CAL import MoroInvCumulativeSobolGaussianRsg
from CAL import MoroInvCumulativeKnuthGaussianRsg
from CAL import InvCumulativeMersenneTwisterGaussianRsg
from CAL import InvCumulativeSobolGaussianRsg
from CAL import InvCumulativeKnuthGaussianRsg
import numpy as np

def StandardNormalGeneration(size, seed = 1, method = 'MT'):
    '''
    正态分布随机数发生器：
    Input:
    size -- 返回随机数矩阵大小，例如(3,2)。
    seed -- 随机数种子
    method -- 生成方法，现在支持'MT'或者'Sobol'
    
    Output:
    size大小的随机数矩阵
    
    '''
    if hasattr(size, '__len__'):
        if len(size) == 1:
            dims = 1
            samples = size[0]
        elif len(size) == 2:
            dims = size[1]
            samples = size[0]
        else:
            raise Exception('#Size parameter should only has 2 axis!')
    elif size is int:
        dims = 1
        samples = size
    else:
        raise Exception('#Size should be integer!')
    
    if method.upper() == 'MT':
        ung = MersenneTwisterUniformRng(seed)
        usg = MersenneTwisterUniformRsg(dims, ung)
        nsg = InvCumulativeMersenneTwisterGaussianRsg(usg)
    elif method.upper() == 'SOBOL':
        usg = SobolRsg(dims, seed)
        nsg = InvCumulativeSobolGaussianRsg(usg)
    elif method.upper() == 'KNUTH':
        ung = KnuthUniformRng(seed)
        usg = KnuthUniformRsg(dims, ung)
        nsg = InvCumulativeKnuthGaussianRsg(usg)
    
    tupleSamples = nsg.batchSimulation(samples)
    return np.array(tupleSamples)

if __name__ == '__main__':
    res = StandardNormalGeneration((1000,2), 100, method = 'MT')
    print res[0][0]
    print type(res)