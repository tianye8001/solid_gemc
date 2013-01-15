#! /bin/tcsh -f

# CaloSim mac/RunTest.mac $dest_prefix.root

set configs = (\
	PVDIS_4mm\
	PVDIS_5mm\
	PVDIS_6mm\
	PVDIS_8mm\
	SIDIS_Forward_4mm\
	SIDIS_Forward_5mm\
	SIDIS_Forward_6mm\
	SIDIS_Forward_8mm\
	SIDIS_Large_4mm\
	SIDIS_Large_5mm\
	SIDIS_Large_6mm\
	SIDIS_Large_8mm	\
	);


foreach config ($configs)
	echo "======================="
	echo Compile $config;
	echo "======================="
	
	set dest_prefix = "$PWD/exe/${config}/";
	
	
	mkdir -vp $dest_prefix
	
	
# rsync -avL include/Config.h $dest_prefix
	ln -svfb  $dest_prefix/Config.h include/Config.h
	
	make clean;
	make -j4;
	
	rsync -avL CaloSimShashlik $dest_prefix
	
	mv -fv include/Config.h~ include/Config.h

	
end

