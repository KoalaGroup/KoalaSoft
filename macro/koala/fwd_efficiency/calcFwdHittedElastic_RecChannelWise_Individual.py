#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'calcFwdHittedElastic_RecChannelWise_Individual.C')
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
                    default="fwd_efficiency_whole_TofE_individual.txt",
                    help="the output file containing forward detector detection efficiency")
parser.add_argument("--digi_dir",
                    default="digi/",
                    help="directory where files are located")
parser.add_argument("--cut_file",
                    help="name of the file containing graphs for the cut")
parser.add_argument("--cut_dir",
                    default='TofE_profile_MoreThan10Evts',
                    help="name of directory containing the graphs for the cut")
parser.add_argument("--branch",
                    default="KoaRecCluster_Smear",
                    help="branch name of cluster")
parser.add_argument("--low_thresh",
                    default='-5',
                    help="lower thresh of the cut in sigma")
parser.add_argument("--high_thresh",
                    default='5',
                    help="higher thresh of the cut in sigma")
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
    command = [exec_bin, macro, fcluster, args.cut_file, fdigi,
               args.branch, args.cut_dir, args.low_thresh, args.high_thresh,
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
