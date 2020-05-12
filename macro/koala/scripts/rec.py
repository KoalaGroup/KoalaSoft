#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_rec.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-o","--output",help="directory where the output files are saved")
parser.add_argument("-s","--suffix",help="suffix of the output")

args = parser.parse_args()
file_list = args.infile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

out_dir = in_dir
if(args.output):
    out_dir = args.output
out_dir = os.path.expanduser(out_dir)

suffix = '_calib.root'
if(args.suffix):
    suffix = args.suffix

# add rec each file in the list
list_decoded = batch.get_list(file_list, '.root', in_dir)
for fin in list_decoded:
    command = [exec_bin, macro, fin, out_dir, suffix]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
