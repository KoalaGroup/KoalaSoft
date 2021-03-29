#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/filterOnFwd.C')
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
parser.add_argument("--fwd1_tlow",
                    default="915",
                    help="lower limit of the time spectrum of fwd1")
parser.add_argument("--fwd1_thigh",
                    default="930",
                    help="higher limit of the time spectrum of fwd1")
parser.add_argument("--fwd2_tlow",
                    default="915",
                    help="lower limit of the time spectrum of fwd2")
parser.add_argument("--fwd2_thigh",
                    default="930",
                    help="higher limit of the time spectrum of fwd2")
parser.add_argument("--window_tlow",
                    default="-10",
                    help="lower limit of the time windown")
parser.add_argument("--window_thigh",
                    default="10",
                    help="higher limit of the time window")
parser.add_argument("--fwd1_alow",
                    default="790",
                    help="higher limit of the pedestal amplitude of fwd1")
parser.add_argument("--fwd1_ahigh",
                    default="1050",
                    help="lower limit of the MIP amplitude of fwd1")
parser.add_argument("--fwd2_alow",
                    default="780",
                    help="higher limit of the pedestal amplitude of fwd2")
parser.add_argument("--fwd2_ahigh",
                    default="1030",
                    help="lower limit of the MIP amplitude of fwd2")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)

# invoking the command
for fin in list_input:
    command = [exec_bin, macro, fin, "koalasim", "KoaFwdDigi",
               args.fwd1_tlow, args.fwd1_thigh, args.fwd2_tlow, args.fwd2_thigh,
               args.window_tlow, args.window_thigh,
               args.fwd1_alow, args.fwd1_ahigh, args.fwd2_alow, args.fwd2_ahigh]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

