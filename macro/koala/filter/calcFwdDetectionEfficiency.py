#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/calcFwdDetectionEfficiency.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-o","--output",
                    default="fwd_efficiency.txt",
                    help="the output file containing forward detector detection efficiency")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the digi file")
parser.add_argument("--fwd1_amp_trigger",
                    default="790",
                    help="fwd1 amplitude trigger")
parser.add_argument("--fwd2_amp_trigger",
                    default="780",
                    help="fwd2 amplitude trigger")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_elist = batch.get_list(args.infile, "_EntryList.root", in_dir)

# open the output file
out_filename = os.path.join(in_dir, args.output)
fout = open(out_filename, 'w')

# invoking the command
for fin, felist in zip(list_input, list_elist):
    command = [exec_bin, macro, fin, felist, args.fwd1_amp_trigger, args.fwd2_amp_trigger]
    print(command)
    # process = subprocess.Popen(command)
    # process.wait()
    with subprocess.Popen(command, stdout=subprocess.PIPE, universal_newlines=True) as process:
        fout.write(process.stdout.read())

fout.close()
