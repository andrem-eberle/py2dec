__doc__ = 'Something just to look at via pydoc.'
import types

class A_classic():
    __doc__ = 'A classic class.'
    
    def A_method(self):
        pass
    
    def AB_method(self):
        pass
    
    def AC_method(self):
        pass
    
    def AD_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass

class B_classic(A_classic,):
    __doc__ = 'A classic class, derived from A_classic.'
    
    def AB_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def B_method(self):
        pass
    
    def BC_method(self):
        pass
    
    def BD_method(self):
        pass
    
    def BCD_method(self):
        pass

class C_classic(A_classic,):
    __doc__ = 'A classic class, derived from A_classic.'
    
    def AC_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def BC_method(self):
        pass
    
    def BCD_method(self):
        pass
    
    def C_method(self):
        pass
    
    def CD_method(self):
        pass

class D_classic(B_classic,C_classic):
    __doc__ = 'A classic class, derived from B_classic and C_classic.'
    
    def AD_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def BD_method(self):
        pass
    
    def BCD_method(self):
        pass
    
    def CD_method(self):
        pass
    
    def D_method(self):
        pass

class A_new(object,):
    __doc__ = 'A new-style class.'
    
    def A_method(self):
        pass
    
    def AB_method(self):
        pass
    
    def AC_method(self):
        pass
    
    def AD_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def A_classmethod(cls,x):
        pass
    A_classmethod = classmethod(A_classmethod)
    
    def A_staticmethod():
        pass
    A_staticmethod = staticmethod(A_staticmethod)
    
    def _getx(self):
        pass
    
    def _setx(self,value):
        pass
    
    def _delx(self):
        pass
    A_property = property(doc='A sample property defined in A.',fset=_setx,fget=_getx,fdel=_delx)
    A_int_alias = int

class B_new(A_new,):
    __doc__ = 'A new-style class, derived from A_new.'
    
    def AB_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def B_method(self):
        pass
    
    def BC_method(self):
        pass
    
    def BD_method(self):
        pass
    
    def BCD_method(self):
        pass

class C_new(A_new,):
    __doc__ = 'A new-style class, derived from A_new.'
    
    def AC_method(self):
        pass
    
    def ABC_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def BC_method(self):
        pass
    
    def BCD_method(self):
        pass
    
    def C_method(self):
        pass
    
    def CD_method(self):
        pass

class D_new(B_new,C_new):
    __doc__ = 'A new-style class, derived from B_new and C_new.\n    '
    
    def AD_method(self):
        pass
    
    def ABD_method(self):
        pass
    
    def ACD_method(self):
        pass
    
    def ABCD_method(self):
        pass
    
    def BD_method(self):
        pass
    
    def BCD_method(self):
        pass
    
    def CD_method(self):
        pass
    
    def D_method(self):
        pass

class FunkyProperties(object,):
    __doc__ = 'From SF bug 472347, by Roeland Rengelink.\n\n    Property getters etc may not be vanilla functions or methods,\n    and this used to make GUI pydoc blow up.\n    '
    
    def __init__(self):
        self.desc = {'x':0}
        pass
    
    class get_desc():
        
        def __init__(self,attr):
            self.attr = attr
            pass
        
        def __call__(self,inst):
            print('Get called')
            print(self)
            print(inst)
            return inst.desc[self.attr]
    
    class set_desc():
        
        def __init__(self,attr):
            self.attr = attr
            pass
        
        def __call__(self,inst,val):
            print('Set called')
            print(self)
            print(inst)
            print(val)
            inst.desc[self.attr] = val
    
    class del_desc():
        
        def __init__(self,attr):
            self.attr = attr
            pass
        
        def __call__(self,inst):
            print('Del called')
            print(self)
            print(inst)
            del inst.desc[self.attr]
    x = property(get_desc('x'), set_desc('x'), del_desc('x'), 'prop x')
submodule = types.ModuleType( __name__ + '.submodule' , 'A submodule, which should appear in its parent\'s summary')
