# Repository for ma-mx scan

### Install MG5aMC + MadDM

Version 2.9.7 of MG5aMC is used - this runs on `python 2.7` and might require some 
python modules like `six` to be installed.

To install run
```
source install.sh
```

### Run MadDM 

An example card for the ma-mx scan is given in the repo. One can adjust it accordingly and then run
```
cd MG5_aMC_v2_9_7/run_relic
python2 ../bin/maddm.py mchi_ma_scan.dat
```

The results will be collected in `mchi_ma_scan/output` that is then processed by the script below to make 
the RD plot.

For 20k points the scan takes about 2 hours to complete.

### Make RD plot

This needs `python3`

```
python3 printRD.py MG5_aMC_v2_9_7/run_relic/ma_mchi_scan
```

NB: one might need to adjust the plotting range. The script might take some time to run
when the number of inputs is big (~5 min for 20k input points).

### To create final exclusion plot

```
python plotCont.py
```
