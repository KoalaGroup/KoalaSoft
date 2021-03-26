#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/scripts/checkFwdDigi.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-s","--suffix",help="suffix of the input file")

args = parser.parse_args()
file_list = args.infile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

suffix = '.root'
if(args.suffix):
    suffix = args.suffix

#
list_file = batch.get_list(file_list, suffix, in_dir)

for fin in list_file:
    command = [exec_bin, macro, fin, 'koalasim']
    print(command)
    process = subprocess.Popen(command)
    process.wait()
