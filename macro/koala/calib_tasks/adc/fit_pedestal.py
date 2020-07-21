#!/usr/bin/python

import argparse
import os
import subprocess
import batch

vmc_dir = os.environ['VMCWORKDIR']
macro = os.path.join(vmc_dir, 'macro/koala/calib_tasks/adc/fit_pedestal.C')
exec_bin = os.path.join(vmc_dir,'build/bin/koa_execute')

# arguments definitions
parser = argparse.ArgumentParser()
parser.add_argument('infile', help='the file list to be processed')
parser.add_argument('-d', '--directory',
                    default='./',
                    help = 'directory where files are located')
parser.add_argument('-s', '--suffix',
                    default='.root',
                    help ='suffix of the input file')
parser.add_argument('--hdir',
                    default='rec_adc',
                    help ='directory for histograms to be fitted')
parser.add_argument('--hsuffix',
                    default='adc',
                    help = 'suffix for histogram name')
parser.add_argument('--seed',
                    default='adc_pedestal_20190902_003449.txt',
                    help = 'pedestal seed file')
parser.add_argument('-o', '--outdir',
                    default='./',
                    help='output directory')

# arguments parsing 
args = parser.parse_args()

file_list = args.infile
in_dir = os.path.expanduser(args.directory)
out_dir = os.path.expanduser(args.outdir)

#
list_infile = batch.get_list(file_list, args.suffix, in_dir)
list_outfile = batch.get_list(file_list, '_pedestal_fit.txt', out_dir)

for fin, fout in zip(list_infile, list_outfile):
    command = [exec_bin, macro, fin, args.hdir,
               args.hsuffix, fout, args.seed]
    print(command)
    process = subprocess.Popen(command)
    process.wait()
