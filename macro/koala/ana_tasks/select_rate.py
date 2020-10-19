#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/ana_tasks/select_rate.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default="_Rate.root",
                    help="suffix of the input file")
parser.add_argument("--ratio_ver_low",
                    help="Low limit of fwd vertical ratio (up/down)")
parser.add_argument("--ratio_ver_high",
                    help="High limit of fwd vertical ratio (up/down)")
parser.add_argument("--ratio_hor_low",
                    help="Low limit of fwd horizontal ratio (in/out)")
parser.add_argument("--ratio_hor_high",
                    help="High limit of fwd horizontal ratio (in/out)")
parser.add_argument("--rate_in_low",
                    help="Low limit of fwd inside rate")
parser.add_argument("--rate_in_high",
                    help="High limit of fwd inside rate")
parser.add_argument("--rate_out_low",
                    help="Low limit of fwd outside rate")
parser.add_argument("--rate_out_high",
                    help="High limit of fwd outside rate")
parser.add_argument("--rate_up_low",
                    help="Low limit of fwd up rate")
parser.add_argument("--rate_up_high",
                    help="High limit of fwd up rate")
parser.add_argument("--rate_down_low",
                    help="Low limit of fwd down rate")
parser.add_argument("--rate_down_high",
                    help="High limit of fwd down rate")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)

# invoking the command
for fin in list_input:
    command = [exec_bin, macro, fin,
               args.ratio_ver_low, args.ratio_ver_high,
               args.ratio_hor_low, args.ratio_hor_high,
               args.rate_in_low, args.rate_in_high,
               args.rate_out_low, args.rate_out_high,
               args.rate_up_low, args.rate_up_high,
               args.rate_down_low, args.rate_down_high]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
