# -*- coding: utf-8 -*-

import ctypes

import os
os.environ['PATH'] = './' + ';' + os.environ['PATH']

def primoTest(y):
    
    
    print "x"*50
    print "start run"
    lib=None
    #xxx

    #lib = ctypes.cdll.LoadLibrary(
    #"/home/ale/pro/build-horizonExtern-Desktop_Qt_5_2_1_GCC_64bit-Debug/libhorizonExtern.so.1.0.0")

    dllToLoad = str(os.path.dirname(os.path.realpath(__file__))) + "/libhorizonExtern.so"

    lib = ctypes.cdll.LoadLibrary(dllToLoad)
                                               
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


def test_boost_python():

    import sys
    
    sys.path.append("/home/ale/pro/build-horizonExtern-Desktop_Qt_5_2_1_GCC_64bit-Release")  
  
    import libhorizonExtern

    p = libhorizonExtern.World()

    p.set("alphaa")

    print(p.greet())
    
    print 50*"x"
    
    test_boost_python_2(libhorizonExtern, 3)

   
def secondoTest(x):
    

    import sys
    
    
    pathFolder = str(os.path.dirname(os.path.realpath(__file__)))
    
    print pathFolder

    #sys.path.append("/home/ale/pro/build-horizonExtern-Desktop_Qt_5_2_1_GCC_64bit-Release")  
  
    sys.path.append(pathFolder)  

    # da notare che il nome del .so deve essere libhorizonExtern.so, ovvero
    # e non libhorizonExtern.so.1.0.0, altrimenti l'import alla riga
    # seguente non lo trova!

    import libhorizonExtern

    return test_boost_python_2(libhorizonExtern, x)
    
    
    
def test_boost_python_2(libhorizonExtern, x):
      
    
      
    hl_a = libhorizonExtern.HL_A.create()

    print hl_a.hello()
 
    print 50*"x"
    
    
    hl_b = libhorizonExtern.HL_B.create(x + 0.34)

    hl_b.set_hl_a(hl_a); 
    
    hl_b.set_extraString_b("__CIAO__");
       
    hl_c = libhorizonExtern.HL_C.create()

    hl_a.hl_c=hl_c;

    hl_b.set_hl_c(hl_a.hl_c);
    
    s = hl_b.hello_b()
   
    print s
 
    return s  
    
    
   
if __name__ == '__main__':

    
    #test_boost_python()
    
    print 100*"-"
    
    secondoTest(5)
    
#    y=5
#    
#    primoTest(y)
    
    pass
    

