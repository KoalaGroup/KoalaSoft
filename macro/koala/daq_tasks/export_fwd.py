#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro_dir = os.path.dirname(os.path.realpath(__file__))

macro = os.path.join(macro_dir, 'export_fwd.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="digi",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the input file")
parser.add_argument("--cluster_dir",
                    default = "calib",
                    help = "directory containing the cluster file")
parser.add_argument("--cluster_suffix",
                    default="_calib.root",
                    help = "suffix of the cluster file")
parser.add_argument("--cluster_branch",
                    default="KoaRecCluster_ThresholdFilter",
                    help = "name of the cluster branch")


args = parser.parse_args()
file_list = args.infile

#
list_file = batch.get_list(file_list, args.suffix, args.directory)
list_cluster = batch.get_list(file_list, args.cluster_suffix, args.cluster_dir)

for fin,fcluster in zip(list_file, list_cluster):
    command = [exec_bin, macro, fin, fcluster, args.cluster_branch]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
