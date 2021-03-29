#!/usr/bin/python

import argparse
import os
import sys
import subprocess
from shutil import copyfile
from shutil import move

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'profile_target_with_energy.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="The file containing the spectrums to be fit")
parser.add_argument("--mom",
                    default="2.2",
                    help="Txt file containing the channel configuration paramters")
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
parser.add_argument("--directory",
                    default="Energy_Individual_-5.0_5.0",
                    help="Directory containing the spectrums in the input ROOT file")
parser.add_argument("--suffix",
                    default="Energy",
                    help="Suffix of the spectrums' name")
parser.add_argument("--geo_file",
                    default="geo_standard.root",
                    help="Suffix of the spectrums' name")

## argument parsing
args = parser.parse_args()

f_spectrum = os.path.expanduser(args.infile)
f_geometry = os.path.expanduser(args.geo_file)
it_nr = args.e_nr

## create directory to contain the text results from each iteration
dir_output = os.path.expanduser(args.infile.replace('.root', f'_target_profile'))
os.makedirs(dir_output, exist_ok=True)

## iteration using the output fit parameters as configuration for the next iteration of fit
for i in range(it_nr):
    print(f'Iterate {i+1} (Ref Energy: {args.e_start+i*args.e_step} MeV):')
    command = [exec_bin, macro, f_spectrum, args.directory, args.suffix, args.mom,
               f'{args.e_start+i*args.e_step:.3f}', f_geometry]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
    move(f_spectrum.replace('.root', f'_target_profile_ref{1000*(args.e_start+i*args.e_step):.0f}keV.txt'), os.path.join(dir_output, f'ref_{1000*(args.e_start+i*args.e_step):.0f}keV.txt'))
    move(f_spectrum.replace('.root', f'_target_profile_ref{1000*(args.e_start+i*args.e_step):.0f}keV.pdf'), os.path.join(dir_output, f'ref_{1000*(args.e_start+i*args.e_step):.0f}keV.pdf'))
