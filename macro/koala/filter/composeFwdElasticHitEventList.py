#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/composeFwdElasticHitEventList.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./digi",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default="_EntryList.root",
                    help="suffix of the input file")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)

# invoking the command
for fin in list_input:
    command = [exec_bin, macro, fin]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

