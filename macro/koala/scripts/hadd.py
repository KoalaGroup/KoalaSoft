#!/usr/bin/python

import argparse
import os
import subprocess
import batch

haddbin = 'hadd'

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("outfile",help="the output summed root file name")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-s","--suffix",help="common suffix of the file")

args = parser.parse_args()
file_list = args.infile
outfile = args.outfile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

suffix = '_result.root'
if(args.suffix):
    suffix = args.suffix

list_decoded = batch.get_list(file_list, suffix, in_dir)
command = [haddbin, os.path.join(in_dir, outfile)]
for fin in list_decoded:
    command.append(fin)

print(command)
process = subprocess.Popen(command)
# wait until process returns, so that mv in next step be meaningful
process.wait()
