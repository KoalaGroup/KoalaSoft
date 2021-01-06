#!/usr/bin/python

# Calculate efficiency with confidence interfal 95%
import argparse
import os
import pandas as pd
import math

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument('-f',
                    action = 'store_true',
                    help="flag determining the format of input file (effieciency clumns exist or not)")

args = parser.parse_args()

# open the output file
if (args.f):
    tb = pd.read_csv(args.infile, delim_whitespace=True, names=['trig1','total1', 'trig2','total2'])
else:
    tb = pd.read_csv(args.infile, delim_whitespace=True, names=['trig1','total1','eff1', 'trig2','total2','eff2'])


p1 = tb['trig1'].sum()/tb['total1'].sum()
p2 = tb['trig2'].sum()/tb['total2'].sum()
n1 = tb['total1'].sum()
n2 = tb['total2'].sum()

z = 1.96 # 95% confidence interfal
e1 = z*math.sqrt(p1*(1-p1)/n1)
e2 = z*math.sqrt(p2*(1-p2)/n2)

print(f'p1: {p1} ({e1}),\t p2: {p2} ({e2})')
