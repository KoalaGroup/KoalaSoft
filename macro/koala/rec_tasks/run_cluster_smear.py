#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_cluster_smear.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-p", "--para_dir",
                    default="./",
                    help="directory for parameter file")
parser.add_argument("-b", "--branch",
                    default="KoaRecCluster_Purification",
                    help="input branch name")
parser.add_argument("-o","--output",
                    default="./",
                    help="directory where the output files are saved")
parser.add_argument("-s","--suffix",
                    default="_smear.root",
                    help="suffix of the input file")
parser.add_argument("--adc_param",
                    default="adc_calib_energy_huagen.txt",
                    help="file name of ADC calib parameters")
parser.add_argument("--tdc_resolution",
                    default="0.03125",
                    help="TDC resolution in ns")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)
para_dir = os.path.expanduser(args.para_dir)
out_dir = os.path.expanduser(args.output)
out_suffix = args.branch.replace('KoaRecCluster','')+'_smear.root'

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_para = batch.get_list(args.infile, "_param.root", para_dir)

for fin, fpara in zip(list_input, list_para):
    command = [exec_bin, macro, fin, fpara, args.branch, out_dir, out_suffix, args.adc_param, args.tdc_resolution]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
