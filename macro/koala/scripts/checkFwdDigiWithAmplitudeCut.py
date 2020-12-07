#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/scripts/checkFwdDigiWithAmplitudeCut.C')
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
parser.add_argument("--fwd1_low",
                    default="790",
                    help="higher limit of the pedestal amplitude of fwd1")
parser.add_argument("--fwd1_high",
                    default="1050",
                    help="lower limit of the MIP amplitude of fwd1")
parser.add_argument("--fwd2_low",
                    default="780",
                    help="higher limit of the pedestal amplitude of fwd2")
parser.add_argument("--fwd2_high",
                    default="1030",
                    help="lower limit of the MIP amplitude of fwd2")

args = parser.parse_args()
in_dir = os.path.expanduser(args.directory)

#
list_file = batch.get_list(args.infile, args.suffix, in_dir)

for fin in list_file:
    command = [exec_bin, macro, fin, 'koalasim', 'KoaFwdDigi',
               args.fwd1_low, args.fwd1_high, args.fwd2_low, args.fwd2_high]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
