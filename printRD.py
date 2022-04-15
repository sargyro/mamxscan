#!/usr/bin/env python

import os, sys, glob

import numpy as np
import scipy.interpolate
from scipy.stats import multivariate_normal
from scipy.interpolate import interp2d
import matplotlib.pyplot as plt
import numpy.ma as ma
import pandas as pd

class RD:
    def __init__(self, name, path, mx, ma, Omegah2):
        self.name = name
        self.path = path
        self.mx = mx
        self.ma = ma
        self.Omegah2 = Omegah2
	
    def show(self):
        print("name = %s , mx = %s , ma = %s , Omega = %s\n" % (self.name, self.mx, self.ma, self.Omegah2))
    
RDlist=[]
MAJOR_TICK_LENGTH = 6
MINOR_TICK_LENGTH = 3
INTERPOLATE=False

def set_mx_ma(obj, mx, ma):
    obj.mx = mx
    obj.ma = ma
    
def set_omega(obj, omega):
    omega = float(omega)
    obj.Omegah2 = omega if omega > 0 else 1e6 # remove -1 thrown when RD too large

def plot(x_list,y_list,z_list):
        
    xy = np.column_stack([x_list.flat, y_list.flat])
    
    if INTERPOLATE:
      # interpolation - doesn't work if input size is too big (>10k points)
      grid_x, grid_y = np.mgrid[x_list.min():x_list.max():10000j, y_list.min():y_list.max():10000j]
      grid_z = scipy.interpolate.griddata(xy,z_list,(grid_x, grid_y), method="cubic")
      grid_z2 = scipy.interpolate.griddata(xy,z_list,(grid_x, grid_y), method="linear")    
      plt.pcolormesh(grid_x, grid_y, ma.masked_invalid(grid_z), cmap='coolwarm', vmin=0, vmax=0.2)
      plt.colorbar()
      plt.contour(grid_x, grid_y, grid_z, colors='k', levels=[0.12])
      #plt.contour(grid_x, grid_y, grid_z2, colors='r', levels=[0.12])
    else:
      # No interpolation
      #plt.tricontourf(x_list, y_list, z_list, levels=[0,0.1176,0.12,0.1224,0.2], cmap='coolwarm', vmin=0, vmax=0.2) # with Planck uncertainty
      plt.tricontourf(x_list, y_list, z_list, levels=[0,0.12,0.2], cmap='coolwarm', vmin=0, vmax=0.2)
    
    plt.axis([x_list.min(),x_list.max(),y_list.min(),y_list.max()])
    plt.xlabel(r"$m_{a}$ [GeV]", fontsize=15)
    plt.ylabel(r"$m_{\chi}$ [GeV]", fontsize=15)
    # Restrict the axis ranges
    #plt.xlim([0,50])
    #plt.ylim([0,50])
    
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    
    axes = plt.gca()
    axes.tick_params("both", which="both", direction="in")
    axes.tick_params("both", which="major", length=MAJOR_TICK_LENGTH)
    axes.tick_params("both", which="minor", length=MINOR_TICK_LENGTH)
    axes.tick_params("x", which="both", top=True)
    axes.tick_params("y", which="both", right=True)
        
    line_x = np.arange(50, 550, 50)
    line_y = [0.5*i for i in line_x]
    plt.plot(line_x, line_y, 'g--')
    plt.savefig('fig.png', dpi=300)
    
def main(): 
    # Get directory names
    for subdir in glob.glob(os.path.join(os.getcwd(), sys.argv[1], 'output/run*')):
        dirname=os.path.basename(subdir)
        RDlist.append(RD(dirname, subdir, 0, 0, 0))
    
    # Open the scan_run_01.txt file and read mx and ma values
    with open(os.path.join(os.getcwd(), sys.argv[1], 'output/scan_run_01.txt')) as f:
        for line in f.readlines():
            if not line.startswith('run'): continue
            [set_mx_ma(x, line.split()[1], line.split()[2]) for x in RDlist if x.name == line.split()[0]]
	    
	    # Get Omega from output file
            with open(os.path.join(os.getcwd(), sys.argv[1], 'output', line.split()[0], 'maddm.out')) as fo:
                for l in fo.readlines():
                    if 'Omega' not in l: continue
                    [set_omega(x, l.split()[-1]) for x in RDlist if x.name == line.split()[0]]
                    break
	    
    # Print list
    [x.show() for x in RDlist]    
    
    plot(np.array([x.ma for x in RDlist]).astype(np.float), 
         np.array([x.mx for x in RDlist]).astype(np.float), 
	 np.array([x.Omegah2 for x in RDlist]).astype(np.float))	

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("./printRD.py DIR")
        sys.exit(1)
    
    if not os.path.isdir(sys.argv[1]):
        print("ERROR %s does not exist" % sys.argv[1])
        sys.exit(2)
    
    main()
