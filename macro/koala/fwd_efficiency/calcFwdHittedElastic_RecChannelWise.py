#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/calcFwdHittedElastic_RecChannelWise.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the input file")
parser.add_argument("-o","--output",
                    default="fwd_efficiency_whole_TofE.txt",
                    help="the output file containing forward detector detection efficiency")
parser.add_argument("--digi_dir",
                    default="digi/",
                    help="directory where files are located")
parser.add_argument("--branch",
                    default="KoaRecCluster_Smear",
                    help="branch name of cluster")
parser.add_argument("--p0",
                    default="450",
                    help="suffix of the input file")
parser.add_argument("--p1",
                    default="79.25",
                    help="suffix of the input file")
parser.add_argument("--p2",
                    default="0.898",
                    help="suffix of the input file")
parser.add_argument("--window",
                    default="20",
                    help="suffix of the input file")
parser.add_argument("--fwd1_thresh_mip",
                    default="1040",
                    help="suffix of the input file")
parser.add_argument("--fwd2_thresh_mip",
                    default="1040",
                    help="suffix of the input file")
parser.add_argument("--fwd1_thresh_daq",
                    default="780",
                    help="suffix of the input file")
parser.add_argument("--fwd2_thresh_daq",
                    default="790",
                    help="suffix of the input file")

args = parser.parse_args()

#
file_list = args.infile
list_fcluster = batch.get_list(file_list, args.suffix, args.directory)
list_fdigi = batch.get_list(file_list, ".root", args.digi_dir)

# open the output file
out_filename = os.path.join(args.directory, args.output)
fout = open(out_filename, 'w')

for fcluster, fdigi in zip( list_fcluster , list_fdigi):
    command = [exec_bin, macro, fcluster, args.branch, fdigi,
               args.p0, args.p1, args.p2, args.window,
               args.fwd1_thresh_mip, args.fwd2_thresh_mip,
               args.fwd1_thresh_daq, args.fwd2_thresh_daq]
    print(command)
    with subprocess.Popen(command, stdout=subprocess.PIPE, universal_newlines=True) as process:
        fout.write(process.stdout.read())

fout.close()

# Calculate efficiency with confidence interfal 95%
import pandas as pd
import math
tb = pd.read_csv(out_filename, delim_whitespace=True, names=['trig1','total1','eff1', 'trig2','total2','eff2'])
p1 = tb['trig1'].sum()/tb['total1'].sum()
p2 = tb['trig2'].sum()/tb['total2'].sum()
n1 = tb['total1'].sum()
n2 = tb['total2'].sum()
z = 1.96 # 95% confidence interfal
e1 = z*math.sqrt(p1*(1-p1)/n1)
e2 = z*math.sqrt(p2*(1-p2)/n2)
print(f'p1: {p1} ({e1}),\t p2: {p2} ({e2})')
