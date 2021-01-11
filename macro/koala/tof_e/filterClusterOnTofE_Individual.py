#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

macro_dir = os.path.dirname(os.path.realpath(__file__))
macro = os.path.join(macro_dir, 'filterClusterOnTofE_Individual.C')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("-d", "--directory",
                    help="directory where files are located",
                    default="./")
parser.add_argument("-s", "--suffix",
                    help="suffix of the cluster file",
                    default="_calib.root")
parser.add_argument("-b", "--branch",
                    help="name of the branch containing the cluster",
                    default="KoaRecCluster_Smear")
parser.add_argument("--mom",
                    default='2.2',
                    help="name of the file containing graphs for the cut")
parser.add_argument("--rec_distance",
                    default='90.4',
                    help="name of the file containing graphs for the cut")
parser.add_argument("--tof_offset",
                    default='480',
                    help="name of the file containing graphs for the cut")
parser.add_argument("--cut_file",
                    help="name of the file containing graphs for the cut")
parser.add_argument("--cut_dir",
                    default='TofE_profile_MoreThan10Evts',
                    help="name of directory containing the graphs for the cut")
parser.add_argument("--fwddir",
                    help="directory where fwd timing files are located")
parser.add_argument("--low_thresh",
                    default='-5',
                    help="lower thresh of the cut in sigma")
parser.add_argument("--high_thresh",
                    default='5',
                    help="higher thresh of the cut in sigma")

args = parser.parse_args()

file_list = args.infile
in_dir = os.path.expanduser(args.directory)
fwd_dir = os.path.expanduser(args.fwddir)

# add rec each file in the list
list_files = batch.get_list(file_list, args.suffix, in_dir)
list_fwd = batch.get_list(file_list, "_FwdHit.root", fwd_dir)

for fin, ffwd in zip(list_files, list_fwd):
    command = [exec_bin, macro, args.mom, args.rec_distance, args.tof_offset,
               fin, args.cut_file, ffwd,
               args.branch, args.cut_dir, "fwdhit_time",
               args.low_thresh, args.high_thresh]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
