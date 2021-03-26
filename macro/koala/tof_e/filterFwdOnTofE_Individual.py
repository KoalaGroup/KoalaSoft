#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/filter/filterFwdOnTofE_Individual.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d","--directory",
                    default="./",
                    help="directory where files are located")
parser.add_argument("--digi_dir",
                    default="digi/",
                    help="directory where files are located")
parser.add_argument("-s","--suffix",
                    default=".root",
                    help="suffix of the input file")
parser.add_argument("--branch",
                    default="KoaRecCluster_Smear",
                    help="branch name of cluster")
parser.add_argument("--cut_file",
                    help="name of the file containing graphs for the cut")
parser.add_argument("--cut_dir",
                    default='TofE_profile_MoreThan10Evts',
                    help="name of directory containing the graphs for the cut")
parser.add_argument("--e_low",
                    default="0.1",
                    help="suffix of the input file")
parser.add_argument("--e_high",
                    default="3.0",
                    help="suffix of the input file")
parser.add_argument("--fwd1_amp_trigger",
                    default="1040",
                    help="suffix of the input file")
parser.add_argument("--fwd2_amp_trigger",
                    default="1040",
                    help="suffix of the input file")

args = parser.parse_args()

#
file_list = args.infile
list_fcluster = batch.get_list(file_list, args.suffix, args.directory)
list_fdigi = batch.get_list(file_list, ".root", args.digi_dir)
list_felist = batch.get_list(file_list, "_EntryList.root", args.digi_dir)

for fcluster, fdigi, felist in zip( list_fcluster , list_fdigi,  list_felist):
    command = [exec_bin, macro, fcluster, args.cut_file,
               fdigi, felist, args.branch,
               args.cut_dir,
               args.e_low, args.e_high,
               args.fwd1_amp_trigger, args.fwd2_amp_trigger]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
