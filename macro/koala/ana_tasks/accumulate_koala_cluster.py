#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/ana_tasks/accumulate_koala_cluster.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument("infile",help="the file list to be processed")
parser.add_argument("--cluster_dir",
                    help="directory where files are located")
parser.add_argument("--cluster_suffix",
                    help="directory where files are located")
parser.add_argument("--digi_dir",
                    help="directory where files are located")
parser.add_argument("--digi_suffix",
                    help="directory where files are located")

args = parser.parse_args()

cluster_dir = os.path.expanduser(args.cluster_dir)
digi_dir = os.path.expanduser(args.digi_dir)

# add rec each file in the list
list_cluster = batch.get_list(args.infile, args.cluster_suffix, cluster_dir)
list_digi = batch.get_list(args.infile, args.digi_suffix, digi_dir)

# invoking the command
for fcluster,fdigi in zip(list_cluster, list_digi):
    command = [exec_bin, macro, fcluster, fdigi]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
