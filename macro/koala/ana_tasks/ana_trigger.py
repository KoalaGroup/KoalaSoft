#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/ana_tasks/ana_trigger.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("--trigger_threshfile",
                    default="cluster_seed_threshold.txt",
                    help="File containing the trigger thresholds for each ADC channel")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)

# add rec each file in the list
list_input = batch.get_list(args.infile, '.root', in_dir)
list_param = batch.get_list(args.infile, '_param.root', in_dir)

# invoking the command
for fin, fparam in zip(list_input, list_param):
    command = [exec_bin, macro, fin, fparam, '_Trigger.root', args.trigger_threshfile]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
