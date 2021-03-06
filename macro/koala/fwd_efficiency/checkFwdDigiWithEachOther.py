#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/checkFwdDigiWithEachOther.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the digi file")

args = parser.parse_args()
in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_elist = batch.get_list(args.infile, "_EntryList.root", in_dir)

for fdigi, felist in zip( list_input,  list_elist):
    command = [exec_bin, macro, fdigi, felist]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
