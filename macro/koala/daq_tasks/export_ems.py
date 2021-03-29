#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/daq_tasks/export_ems.C')
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
parser.add_argument("--elist_suffix",
                    help="suffix of the file containing the event list, empty if not used")
parser.add_argument("--elist_dir",
                    default="/",
                    help="directory containing the event list")
parser.add_argument("--elist_name",
                    default="ems_rate_elist",
                    help="name of the event list")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)

if args.elist_suffix:
    list_elist = batch.get_list(args.infile, args.elist_suffix, in_dir)
    for fin, felist in zip(list_input, list_elist):
        command = [exec_bin, macro, fin, felist, args.elist_dir, args.elist_name]
        print(command)
        process = subprocess.Popen(command)
        process.wait()
else:
    for fin in list_input:
        command = [exec_bin, macro, fin]
        print(command)
        process = subprocess.Popen(command)
        process.wait()
