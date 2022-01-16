#!/usr/bin/env bash

original_dir=$PWD
wget https://launchpad.net/mg5amcnlo/2.0/2.9.x/+download/MG5_aMC_v2.9.7.tar.gz
tar -zxf MG5_aMC_v2.9.7.tar.gz 
rm MG5_aMC_v2.6.5.tar.gz 
mg_dir=${original_dir}/MG5_aMC_v2_9_7

git clone ssh://git@gitlab.cern.ch:7999/lhc-dmwg-material/model-repository.git

cd ${mg_dir}/models
cp -r ${original_dir}/model-repository/models/Pseudoscalar_2HDM .

# install MadDM
run_dir=${mg_dir}/run_relic
mkdir ${run_dir}
cd ${run_dir}
cat > tmp_install  << EOF
install maddm
EOF
python ${mg_dir}/bin/mg5_aMC tmp_install
rm tmp_install

# Link the scan dat file
ln -s ../../mchi_ma_scan.dat .

return 0
