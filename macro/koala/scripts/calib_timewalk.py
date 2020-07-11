#!/usr/bin/python

import argparse
import os
import subprocess
import batch

# macros to be wrapped
vmc_dir = os.environ['VMCWORKDIR']
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

macro_fillHistogram = os.path.join(vmc_dir, 'macro/koala/calib_tasks/tdc/fillHistogram.C')
macro_fillAmpVsTime = os.path.join(vmc_dir, 'macro/koala/calib_tasks/tdc/fillAmpVsTime.C')
macro_fitHistogram = os.path.join(vmc_dir, 'macro/koala/calib_tasks/tdc/fitHistogram.C')
macro_fillGraph = os.path.join(vmc_dir, 'macro/koala/calib_tasks/tdc/fillGraph.C')
macro_fitGraph = os.path.join(vmc_dir, 'macro/koala/calib_tasks/tdc/fitGraph.C')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("outfile",help="the output file containing fit result")
parser.add_argument("-i","--input",help="directory where input files are located")
parser.add_argument("-o","--output",help="directory where the output files are saved")

args = parser.parse_args()

file_list = args.infile
outfile = args.outfile

in_dir = './'
if(args.input):
    in_dir = args.input
in_dir = os.path.expanduser(in_dir)

out_dir = in_dir
if(args.output):
    out_dir = args.output
out_dir = os.path.expanduser(out_dir)

################## real job ########################################

# 1. fill the adc and tdc histograms
list_decoded = batch.get_list(file_list, '.root', in_dir)
for fin in list_decoded:
    command = [exec_bin, macro_fillHistogram, fin, out_dir]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

for fin in list_decoded:
    command = [exec_bin, macro_fillAmpVsTime, fin, out_dir]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

# 2. fit the adc and tdc spectrum
list_result = batch.get_list(file_list, '_result.root', out_dir)
for fin in list_result:
    command = [exec_bin, macro_fitHistogram, fin, out_dir]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

# # 3. fill the time_walk graph and time_shift graph
list_params = batch.get_list(file_list, '_result_amp.txt', out_dir)
graph_file = os.path.join(out_dir, outfile)

command = [exec_bin, macro_fillGraph, graph_file] + list_params
print(command)
process = subprocess.Popen(command)
process.wait()

# # 4. fit time walk graphs
command = [exec_bin, macro_fitGraph, graph_file]
print(command)
process = subprocess.Popen(command)
process.wait()
