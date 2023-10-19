greadev: greadev.cxx
	g++ $< -g -O0 -o $@ -I`genie-config --topsrcdir` `genie-config --libs` \
		`root-config --cflags --glibs --evelibs` -lMathMore -lEGPythia6 -L$(PYTHIA6) -lPythia6 \
		`xml2-config --libs` `log4cpp-config --libs` `lhapdf-config --ldflags`