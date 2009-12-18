/* HdfUtil test code                  *
 * Developed by Fredrik Orderud, 2009 */
#include "h5util.hpp"

using namespace std;
typedef boost::numeric::ublas::vector<float> Vector;
typedef boost::numeric::ublas::matrix<float> Matrix;

template <class T>
struct NdTable {
    std::vector<size_t> dims;
    std::vector<T>      data;
};

static void GenerateTestData (int & a, float & b, 
                              std::vector<int> & aa, std::vector<float> & ab, 
                              Vector & va, Matrix & ma,
                              std::string & sa,
                              NdTable<float> & table) {
    const size_t N = 10;
    
    a = 7;
    b = 3.14f;

    aa.resize(N);
    for (size_t i = 0; i < N; i++)
        aa[i] = i;
    ab.resize(N);
    for (size_t i = 0; i < N; i++)
        ab[i] = 0.5f * i;

    va.resize(N);
    for (size_t i = 0; i < N; i++)
        va(i) = 0.3f*i;

    const int I = 2, J = 3;
    ma.resize(I,J);
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++)
            ma(i,j) = 0.2f*i + 0.5f*j;

    // text string
    sa = "test";

    // 3D table with dimensions (2,3,4) 
    table.dims.resize(3);
    table.dims[0] = 2;
    table.dims[1] = 3;
    table.dims[2] = 4;
    table.data.resize(2*3*4);
    for (size_t i = 0; i < 2*3*4; i++)
        table.data[i] = (float)i;
}


void FileWrite (const std::string & filename) {
    using namespace hdfutil;
    //H5::Exception::dontPrint();
    H5::H5File h5file = H5::H5File(filename,  H5F_ACC_TRUNC);

    int                 a = -1;
    float               b = -1.0f;
    std::vector<int>   aa;
    std::vector<float> ab;
    Vector             va;
    Matrix             ma;
    std::string sa;
    NdTable<float> table;
    GenerateTestData(a, b, aa, ab, va, ma, sa, table);

    // write values & arrays to file
    WriteValue        (h5file, "a",  a );
    WriteValue        (h5file, "b",  b );
    WriteVector<float>(h5file, "va", va);
    WriteMatrix<float>(h5file, "ma", ma);
    WriteString       (h5file, "sa", sa);

    H5::Group arrays = h5file.createGroup("arrays");
    WriteArray        (arrays, "aa", aa);
    WriteArray        (arrays, "ab", ab);

    WriteTable<float>(h5file, "table", table.dims, table.data);
}

void FileLoad (const std::string & filename) {
    using namespace hdfutil;
    //H5::Exception::dontPrint();
    H5::H5File h5file = H5::H5File(filename, H5F_ACC_RDONLY);

    int                 a = -1,    ref_a = -1;
    float               b = -1.0f, ref_b = -1.0;
    std::vector<int>   aa(10), ref_aa;
    std::vector<float> ab(10), ref_ab;
    Vector             va,     ref_va;
    Matrix             ma,     ref_ma;
    std::string        sa,     ref_sa;
    NdTable<float>     table,  ref_table;
    GenerateTestData(ref_a, ref_b, ref_aa, ref_ab, ref_va, ref_ma, ref_sa, ref_table);

    // read data from file
    a  = ReadValue<int>   (h5file, "a");
    b  = ReadValue<float> (h5file, "b");
    va = ReadVector<float>(h5file, "va");
    ma = ReadMatrix<float>(h5file, "ma");
    sa = ReadString       (h5file, "sa");

    H5::Group arrays = h5file.openGroup("arrays");
    aa = ReadArray<int>   (arrays, "aa");
    ab = ReadArray<float> (arrays, "ab");

    ReadTable<float>(h5file, "table", table.dims, table.data);
}

int main () {
    const std::string filename("TempFile.h5");

    FileWrite(filename);
    FileLoad(filename);

    return 0;
}
