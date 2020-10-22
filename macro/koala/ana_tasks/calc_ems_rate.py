#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/ana_tasks/calc_ems_rate.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default="_EmsRawEvent.root",
                    help="suffix of the input file")
parser.add_argument("-w","--window" ,
                    default="2",
                    help="Half size of the event window")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_output = batch.get_list(args.infile, "_Rate.root", in_dir)

# invoking the command
for fin, fout in zip(list_input, list_output):
    command = [exec_bin, macro, fin, fout, args.window]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
