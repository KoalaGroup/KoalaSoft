#!/usr/bin/python

import argparse
import os
import sys
import subprocess
from shutil import copyfile

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'getFwdCoverageRatio.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="The file containing the spectrums to be fit")
parser.add_argument("--geometry",
                    default="geo_standard.root",
                    help="Txt file containing the channel configuration paramters")

## argument parsing
args = parser.parse_args()

## the first iteration use the command line config files
print(f'No offset')
command = [exec_bin, macro, args.infile, args.geometry]
print(command)
process = subprocess.Popen(command)
process.wait()

## iteration using the output fit parameters as configuration for the next iteration of fit
for i in range(10):
    print(f'Offset {(i+1)*0.5}:')
    command = [exec_bin, macro, args.infile, args.geometry,f'{0.5*(i+1)}']
    print(command)
    process = subprocess.Popen(command)
    process.wait()

    print(f'Offset {-(i+1)*0.5}:')
    command = [exec_bin, macro, args.infile, args.geometry,f'{-0.5*(i+1)}']
    print(command)
    process = subprocess.Popen(command)
    process.wait()
