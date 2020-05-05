#!/usr/bin/python

import argparse
import os
import subprocess
import batch

haddbin = 'hadd'

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")

args = parser.parse_args()
file_list = args.infile

out_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

list_decoded = batch.get_list(file_list, '_result.root', in_dir)
command = [haddbin, os.path.join(in_dir, "P_2.6_result.root")]
for fin in list_decoded:
    command.append(fin)

print(command)
process = subprocess.Popen(command)
# wait until process returns, so that mv in next step be meaningful
process.wait()
