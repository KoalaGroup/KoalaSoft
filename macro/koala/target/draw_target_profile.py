#!/usr/bin/python

import argparse
import os
import sys
import subprocess
from shutil import copyfile
from shutil import move

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'draw_target_profile.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("directory",help="The file containing the spectrums to be fit")
parser.add_argument("--e_start",
                    default="0.12",
                    type = float,
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--e_step",
                    default="0.05",
                    type = float,
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--e_nr",
                    default="30",
                    type = int,
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--zoffset_si1",
                    default="0",
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--zoffset_si2",
                    default="0",
                    help="Txt file containing the channel configuration paramters")

## argument parsing
args = parser.parse_args()

it_nr = args.e_nr

## iteration using the output fit parameters as configuration for the next iteration of fit
for i in range(it_nr):
    print(f'Iterate {i+1} (Ref Energy: {args.e_start+i*args.e_step} MeV):')
    ftxt = os.path.join(args.directory, f'ref_{1000*(args.e_start+i*args.e_step):.0f}keV.txt')
    command = [exec_bin, macro, ftxt, args.zoffset_si1, args.zoffset_si2]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
