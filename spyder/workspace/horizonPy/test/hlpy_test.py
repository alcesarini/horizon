# -*- coding: utf-8 -*-

import ctypes



def primoTest(y):
    
    
    print "x"*50
    print "start run"
    lib=None


    lib = ctypes.cdll.LoadLibrary("/home/ale/pro/build-horizonExtern-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonExtern.so.1.0.0")

                                               
    lib.ext_HE_TEST_INT_EXTERN_LINK.restype = None
    lib.ext_HE_TEST_INT_EXTERN_LINK.argtypes =[ctypes.POINTER(ctypes.c_int)]                                              

 
    x = ctypes.c_int()
    
    x.value = y;

    lib.ext_HE_TEST_INT_EXTERN_LINK(ctypes.byref(x)) 
       
    print "post run"
    
    print "il risultato è "
    
    print x.value



   
    
    #sys.modules[__name__].__dict__.clear()
 
    print "end run"
    
    
    return x.value
    
    
if __name__ == '__main__':
    
    y=5
    
    primoTest(y)
    
    pass
    

