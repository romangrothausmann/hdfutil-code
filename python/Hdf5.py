# Hdf5 import/export script
# Depends on the 'PyTables' library (http://www.pytables.org/).
# by Fredrik Orderud, 2008
from numpy import array
import tables


class Hdf5Struct :
    """Class for HDF5 datastructures."""
#

def Import (filename):
    print "Importing object to HDF5..."
    # open HDF5 file
    h5f = tables.openFile(filename, "r")
    
    obj = Hdf5Struct()
    _ImportStruct(h5f.root, obj)
    
    h5f.close()
    print "[done]"
    return obj
#
def _ImportStruct (h5f, obj):
    for name in dir(h5f):
        if name[0] == '_':
            continue # skip (private) fields starting with an underscore

        val = getattr(h5f, name)
        try:
            setattr(obj, name, val.read())
        except:
            setattr(obj, name, Hdf5Struct())
            _ImportStruct(val, getattr(obj, name)) #recursive parsing
#


def Export (obj, filename):
    print "Exporting object to HDF5..."
    # create new HDF5 file
    h5f = tables.openFile(filename, "w", title="serialized python object")
    
    _ExportStruct(h5f, '/', obj)
    
    h5f.close()
    
    # strip time-stamp info.
    os.system('HdfTimeStrip '+filename)
    
    print "[done]"
#
def _ExportStruct (h5f, location, obj) :
    for name in dir(obj):
        if name[0] == '_':
            continue # skip (private) fields starting with an underscore
        
        val = getattr(obj, name)
        if isinstance(val, Hdf5Struct):
            h5f.createGroup(location, name)
            _ExportStruct(h5f, location+name+'/', val) #recursive processing
        else:
            h5f.createArray(location, name, val)
#


def TestExport (filename):
    x = Hdf5Struct()
    x.scalint   = 3
    x.scalfloat = 3.14
    x.array     = array([ [1,2],[3,4] ])
    x.string    = 'Hello HDF5!'
    
    x.x = Hdf5Struct()
    x.x.a = 1
    
    Export(x, filename)
#

if __name__ == "__main__":
    TestExport('delme.h5')
    obj = Import('delme.h5')
