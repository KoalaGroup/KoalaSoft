#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_rec_clusterfilter.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-o","--output",
                    default="./",
                    help="directory where the output files are saved")
parser.add_argument("-s","--suffix",
                    default="_calib.root",
                    help="suffix of the output")
parser.add_argument("--pedestal",
                    default="adc_pedestal_20190902_003449.txt")
parser.add_argument("--adc",
                    default="adc_calib_energy_huagen.txt")
parser.add_argument("--tdc",
                    default="tdc_calib_shift.txt")
parser.add_argument("--seed",
                    default="cluster_seed_threshold.txt")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)
out_dir = os.path.expanduser(args.output)

# add rec each file in the list
list_decoded = batch.get_list(args.infile, '.root', in_dir)
for fin in list_decoded:
    fpara = fin.replace(".root","_param.root")
    command = [exec_bin, macro, fin, fpara, out_dir, args.suffix,
               args.pedestal,
               args.adc,
               args.tdc,
               args.seed]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
