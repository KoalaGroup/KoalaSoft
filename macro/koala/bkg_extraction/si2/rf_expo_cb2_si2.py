#!/usr/bin/python

import argparse
import os
import sys
import subprocess
from shutil import copyfile

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'rf_expo_cb2_si2.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="The file containing the spectrums to be fit")
parser.add_argument("--config",
                    default="rf_expo_cb2_config_si2.txt",
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--directory",
                    default="rec_cluster_energy_FirstHit",
                    help="Directory containing the spectrums in the input ROOT file")
parser.add_argument("--suffix",
                    default="cluster_energy_firstHit",
                    help="Suffix of the spectrums' name")
parser.add_argument("--iterate_nr",
                    type = int,
                    default="6",
                    help="Iteration number")

## argument parsing
args = parser.parse_args()

f_spectrum = os.path.expanduser(args.infile)
f_config = os.path.expanduser(args.infile.replace('.root', f'_{args.directory}_FitExpoCB2.txt'))
it_nr = args.iterate_nr

## create directory to contain the text results from each iteration
dir_output = os.path.expanduser(args.infile.replace('.root', f'_{args.directory}_FitExpoCB2'))
os.makedirs(dir_output, exist_ok=True)

## the first iteration use the command line config files
print(f'Init fit...')
init_config = os.path.expanduser(args.config)
copyfile(init_config, os.path.join(dir_output,'channels_0.txt'))

command = [exec_bin, macro, f_spectrum, init_config, args.directory, args.suffix]
print(command)
process = subprocess.Popen(command)
process.wait()
copyfile(f_config, os.path.join(dir_output,'channels_1.txt'))

## iteration using the output fit parameters as configuration for the next iteration of fit
for i in range(it_nr):
    print(f'Iterate {i+1}:')
    command = [exec_bin, macro, f_spectrum, f_config, args.directory, args.suffix]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
    copyfile(f_config, os.path.join(dir_output,f'channels_{i+2}.txt'))

print(f'In total: {it_nr+1} iteration completed!')
