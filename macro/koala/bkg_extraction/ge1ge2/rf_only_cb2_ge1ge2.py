#!/usr/bin/python

import argparse
import os
import sys
import subprocess
from shutil import copyfile

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'rf_only_cb2_ge1ge2.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="The file containing the spectrums to be fit")
parser.add_argument("--channel_config",
                    default="rf_only_cb2_config_ge1ge2.txt",
                    help="Txt file containing the channel configuration paramters")
parser.add_argument("--strip_config",
                    help="Optional. Txt file containing the strip configuration paramters. If not provided, the parameters will be calculated from geometry")
parser.add_argument("--geo_file",
                    default="geo_standard.root",
                    help="ROOT file containing the geometry model")
parser.add_argument("--directory",
                    default="no_mip_Ge1Ge2",
                    help="Directory containing the spectrums in the input ROOT file")
parser.add_argument("--suffix",
                    default="nomip",
                    help="Suffix of the spectrums' name")
parser.add_argument("--mom",
                    help="Beam momentum. Must be provided when no strip configuration is provided")
parser.add_argument("--iterate_nr",
                    type = int,
                    default="12",
                    help="Iteration number")

## argument parsing
args = parser.parse_args()

f_spectrum = os.path.expanduser(args.infile)
f_channel_config = os.path.expanduser(args.infile.replace('.root', f'_{args.directory}_FitOnlyCB2_Channels.txt'))
f_strip_config = os.path.expanduser(args.infile.replace('.root', f'_{args.directory}_FitOnlyCB2_Strips.txt'))
f_geometry = os.path.expanduser(args.geo_file)
it_nr = args.iterate_nr

## create directory to contain the text results from each iteration
dir_output = os.path.expanduser(args.infile.replace('.root', f'_{args.directory}_FitOnlyCB2'))
os.makedirs(dir_output, exist_ok=True)

## the first iteration use the command line config files
print(f'Init fit...')
init_channel_config = os.path.expanduser(args.channel_config)
copyfile(init_channel_config, os.path.join(dir_output,'channels_0.txt'))

if args.strip_config is not None:
    init_strip_config = os.path.expanduser(args.strip_config)
    copyfile(init_strip_config, os.path.join(dir_output,'strips_0.txt'))
    command = [exec_bin, macro, f_spectrum, init_channel_config, init_strip_config,
               f_geometry, args.directory, args.suffix]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
elif args.mom is None:
    sys.exit('If strip configuration file not provided, beam momentum should be provided!')
else:
    command = [exec_bin, macro, f_spectrum, init_channel_config, 'null',
               f_geometry, args.directory, args.suffix,
               'true', args.mom]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

copyfile(f_strip_config, os.path.join(dir_output,'strips_1.txt'))
copyfile(f_channel_config, os.path.join(dir_output,'channels_1.txt'))

## iteration using the output fit parameters as configuration for the next iteration of fit
for i in range(it_nr):
    print(f'Iterate {i+1}:')
    command = [exec_bin, macro, f_spectrum, f_channel_config, f_strip_config,
               f_geometry, args.directory, args.suffix]
    print(command)
    process = subprocess.Popen(command)
    process.wait()

    copyfile(f_strip_config, os.path.join(dir_output,f'strips_{i+2}.txt'))
    copyfile(f_channel_config, os.path.join(dir_output,f'channels_{i+2}.txt'))

print(f'In total: {it_nr} iteration completed!')
