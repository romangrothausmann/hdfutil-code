<!doctype html public "-//w3c//dtd html 4.0 transitional//en">
<html>
<head>
   <title>HDF5 utilities</title>
   <link rel="Stylesheet" type="text/css" href="style.css">
   <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body>


<h1>HDF5 utilities</h1>
<b>Hdfutil</b> is a collection of utilities to ease the exchange of HDF5 files between C++, Matlab and Python. The long term goal is integration into the main HDF5 distribution.
<p>

License: <a href="http://www.opensource.org/licenses/bsd-license.php">BSD</a>.
<p>


<h3>Matlab HdfImport/HdfExport</h3>
Simple (de)serialization of Matlab datastructures to/from HDF5 files [<a href="http://hdfutil.svn.sourceforge.net/viewvc/hdfutil/matlab.tar.gz?view=tar">download</a>].

<h3>Python Hdf5</h3>
Simple (de)serialization of Python datastructures to/from HDF5 files [<a href="http://hdfutil.svn.sourceforge.net/viewvc/hdfutil/python.tar.gz?view=tar">download</a>].

<h3>C++ HDF5 utility functions</h3>
Support function for the HDF5 C++ library for simple (de)serialization of scalars, vectors, matrices and N-dim tables of "any" datatype to HDF5 files [<a href="http://hdfutil.svn.sourceforge.net/viewvc/hdfutil/cpp.tar.gz?view=tar">download</a>].

<h3>HdfTimeStrip</h3>
HdfTimeStrip is a command-line utility to strip time-stamp information from HDF5 files, so that HDF5 files of identical content become binary duplicates [<a href="http://hdfutil.svn.sourceforge.net/viewvc/hdfutil/HdfTimeStrip.tar.gz?view=tar">download</a>, <a href="https://sourceforge.net/projects/hdfutil/files/HdfTimeStrip.exe/download">Win32 binary</a>].

<h3>Development status</h3>
The utilities are fairly feature complete, and should be usable on most platforms "out of the box". There is, however, limited support for handling of dataset attributes in the current implementation. Certain datatypes, like e.g. complex numbers, are also not implemented at the time being. It should be straightforward to extend the implementation to suport any missing feature of desire. In that case, please send a patch to the project, so others can also benefit from your extensions.

<h3>Links</h3>
<ul>
<li> <a href="http://www.hdfgroup.org/HDF5/">HDF5</a> home page.
<li> <a href="http://www.hdfgroup.org/hdf-java-html/hdfview/">HDFView</a> file content viewer.
<li> <a href="http://sourceforge.net/projects/hdfutil/">project page</a> on sourceforge (bug reports, patces &c.).
</ul>


<br><br>
<p align="right">
Last modified <?php echo date("Y-m-d", getlastmod()); ?>.
</p>

</body>
</html>
