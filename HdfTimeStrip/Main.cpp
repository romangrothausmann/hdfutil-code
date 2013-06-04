const char PROGRAM_HEADER1[] = "HdfTimeStrip, Copyright (c) 2010-2012 Fredrik Orderud.";
const char PROGRAM_HEADER2[] = "Removes time-stamp information from HDF5 files, so that identical HDF5 files become binary duplicates.";

/* Dependencies:
   - The HDF5 library 1.8 or newer.
   - Environment variable: HDF_ROOT
   - Windows tip: Buid against static HDF5 libraries to avoid any DLL dependencies.
*/

 // auto-linking of HDF5 libraries
#ifdef _WIN32
#  ifdef _DEBUG
#    ifdef HDF5CPP_USEDLL
#      pragma comment(lib,"hdf5ddll.lib")
#      pragma comment(lib,"hdf5_cppddll.lib")
#    else
#      pragma comment(lib,"hdf5d.lib")
#      pragma comment(lib,"hdf5_cppd.lib")
#    endif
#  else
#    ifdef HDF5CPP_USEDLL
#      pragma comment(lib,"hdf5dll.lib")
#      pragma comment(lib,"hdf5_cppdll.lib")
#    else
#      pragma comment(lib,"hdf5.lib")
#      pragma comment(lib,"hdf5_cpp.lib")
#    endif
#  endif
#endif

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <H5Cpp.h>


/** Copy each scalar/vector/matrix dataset element. */
static void parse_dataset (const H5::DataSet & in_dset, H5::DataSet & out_dset) {
    H5::DataType dtype = in_dset.getDataType();
    hsize_t      size  = in_dset.getStorageSize();

    std::vector<unsigned char> buffer((unsigned int)size);
	in_dset.read  (&buffer[0], dtype);
	out_dset.write(&buffer[0], dtype);
}


/** Read/write each group of datasets. */
static void parse_group (const H5::CommonFG & in_grp, H5::CommonFG & out_grp) {
    using namespace H5;
    hsize_t N = in_grp.getNumObjs();
    for (size_t i = 0; i < N; i++) {
        std::string name = in_grp.getObjnameByIdx(i);
        H5G_obj_t   type = in_grp.getObjTypeByIdx(i);

        if        (type == H5G_GROUP) {
            Group in_child  = in_grp.openGroup(name);
            Group out_child = out_grp.createGroup(name);
            // recursive parsing of child groups
            parse_group(in_child, out_child);
        } else if (type == H5G_DATASET) {
            DataSet   in_dset = in_grp.openDataSet(name);
            DataType  dtype   = in_dset.getDataType();
            DataSpace dspace  = in_dset.getSpace();

			// disable time-stamping of new datasets
			DSetCreatPropList plist;
			H5Pset_obj_track_times(plist.getId(), false);
            // copy dataset content
            DataSet out_dset = out_grp.createDataSet(name, dtype, dspace, plist);
            parse_dataset(in_dset, out_dset);
        } else
            throw std::logic_error("Unsupported object type");
    }
}


/** Name of temp file used when no output is specified. */
const static std::string TEMP_FILE = "temp_hdftimestrip.h5";


/** Program entry point. */
int main (int argc, const char* argv[]) {
    using namespace std;
    cout << PROGRAM_HEADER1 << endl;

 	if (argc < 2) {
		cout << PROGRAM_HEADER2 << endl
             << endl
             << "USAGE: HdfTimeStrip src_file [dst_file]" << endl;
		return -1;
	}

	// determine input/output filenames
	string in_file  = argv[1];
	string out_file = TEMP_FILE;
	if (argc >= 3)
		out_file = argv[2];

    cout << "Loading " << in_file << "..." << endl;
	try {
		// parse input & generate output
		H5::H5File input (in_file,  H5F_ACC_RDONLY);
		H5::H5File output(out_file, H5F_ACC_TRUNC);
		parse_group(input, output);
    } catch (const std::exception & e) {
        cerr << e.what() << endl;
        remove(out_file.c_str());
        return -1;
    }

	// replace input file if no output is specifiec
	if (out_file == TEMP_FILE) {
        cout << "Writing to " << in_file << "..." << endl;
		int result  = remove(in_file.c_str());
		    result |= rename(out_file.c_str(), in_file.c_str());
		return result;
	} else
        cout << "Writing to " << out_file << "..." << endl;


    cout << "[done]" << endl;
    return 0;
}
