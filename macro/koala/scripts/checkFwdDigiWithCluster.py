#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/scripts/checkFwdDigiWithCluster.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",help="directory where files are located")
parser.add_argument("-s","--suffix",help="suffix of the input file")
parser.add_argument("--cluster_dir",
                    default="calib")
parser.add_argument("--cluster_suffix",
                    default="_calib_ThresholdFilter_smear.root")
parser.add_argument("--cluster_br",
                     default="KoaRecCluster_Smear")

args = parser.parse_args()
file_list = args.infile

in_dir = './'
if(args.directory):
    in_dir = args.directory
in_dir = os.path.expanduser(in_dir)

suffix = '.root'
if(args.suffix):
    suffix = args.suffix

#
list_file = batch.get_list(file_list, suffix, in_dir)
list_fcluster = batch.get_list(file_list, args.cluster_suffix, args.cluster_dir)

for fin, fcluster in zip( list_file , list_fcluster):
    command = [exec_bin, macro, fin, fcluster, args.cluster_br]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
