#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/ana_tasks/filterOnRate.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-o","--output",
                    default="rate_select_efficiency.txt",
                    help="the output file containing selection efficiency")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the input file")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_rate = batch.get_list(args.infile, "_Rate_Selected.root", in_dir)
list_elist = batch.get_list(args.infile, "_EntryList.root", in_dir)

# open the output file
out_filename = os.path.join(in_dir, args.output)
fout = open(out_filename, 'w')

# invoking the command
for fin, frate, felist in zip(list_input, list_rate, list_elist):
    command = [exec_bin, macro, fin, frate, felist]
    print(command)
    # process = subprocess.Popen(command)
    # process.wait()
    with subprocess.Popen(command, stdout=subprocess.PIPE, universal_newlines=True) as process:
        fout.write(process.stdout.read())

fout.close()
