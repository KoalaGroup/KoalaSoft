#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_cluster_purification_MultipleMode.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default="_calib.root",
                    help="suffix of the input file")
parser.add_argument("-b","--branch",
                    default="KoaRecCluster_ThresholdFilter",
                    help="suffix of the input file")
parser.add_argument("-p", "--para_dir",
                    default="./",
                    help="directory for parameter file")
parser.add_argument("-t","--threshold" ,
                    default="7",
                    help="suffix of the output")
parser.add_argument("--thresh_file" ,
                    default="",
                    help="channel-wise threshold setting file")
parser.add_argument("-m","--mode" ,
                    default="multiple",
                    help="mode of threshold setting: multiple, abosulte or percentage")

args = parser.parse_args()

in_dir = os.path.expanduser(args.directory)
para_dir = os.path.expanduser(args.para_dir)

thresh_file = ""
if args.thresh_file != "":
    thresh_file = os.path.expanduser(args.thresh_file)

if args.mode == 'absolute':
    macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_cluster_purification_AbsoluteMode.C')
elif args.mode == 'percentage':
    macro = os.path.join(vmc_dir, 'macro/koala/rec_tasks/run_cluster_purification_PercentageMode.C')

# add rec each file in the list
list_input = batch.get_list(args.infile, args.suffix, in_dir)
list_para = batch.get_list(args.infile, "_param.root", para_dir)

# invoking the command
for fin, fpara in zip(list_input, list_para):
    command = [exec_bin, macro, fin, fpara, args.branch, args.threshold, thresh_file]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
