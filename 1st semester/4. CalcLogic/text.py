class Counter:
    def __init__(self,start=0):
        self._count=start
        
    def plus(self,delta=1):
        self._count += delta
        
    def get_count(self):
        return self._count
     
class Flag:
    def __init__(self,start=0):
        self._val=start
        
    def inv(self):
        self._val = not self._val
        
    def get_flag(self):
        return self._val
 
class Coords:
    def __init__(self,x=0,y=0):
        self._x=x; self._y=y
    
    def step(self,side):
        assert(sude in 'nows')
        if side=='o':
            self._x+=1
        elif side=='w':
            self._x-=1
        elif side=='n':
            self._y+=1
        else:
            self._y-=1

class OrdinaryRob(Robot):
    def __init__(self,r):
        self._rob=r
        
    def step(self,side):
        self._rob.step(side)
        
    def is_bord(self,side):
        return self._rob.is_bord(side)

    def mark(self):
        self._rob.mark()

    def is_mark(self):
        return self._rob.is_mark()
        
    def get_tmpr(self):
        return self._rob.get_tmpr()

class RobStepCount(OrdinaryRob,Counter):
        def __init__(self,r):
            super(OrdinaryRob,self).__init__(r)
            super(Counter,self).__init__()
            
        def step(self,side):
            self.step(side)
            self.plus()
             
class RobStepMark(OrdinaryRob):
        def __init__(self,r):
            super().__init__(r)
            
        def step(self,side):
            self.step(side)
            self.mark()
            
class RobStepChessMark(OrdinaryRob,Flag):
    def __init__(self,r,start):
        super(OrdinaryRob,self).__init__(r)
        super(Flag,self).__init__(start)

    def step(self,side):
        self.step(side)
        if self.get_flag()==1:
            self.mark()
        self.inv() 
            
class RobStepSave(OrdinaryRob):
    def __init__(self,r):
        super().__init__(r)
        self._back_path=''
        
    def step(self,side):
        self.step(side)
        self._back_path=inv(side)+self._back_path

def steps_toangle(r, side):
    assert(side in {"ws", "sw", "so", "os", "no", "on", "nw", "wn"})
    while r.is_bord(side[0]) == 0 or r.is_bord(side[1]) == 0: # Робот не в углу
        steps_tolim(r, side[0])
        steps_tolim(r, side[1])
    
def from_sw_bypass(r):
    side = "o"
    steps_tolim(r, side)
    while r.is_bord("n") == 0:
        r.step("n")
        side=inv_side(side)
        steps_tolim(r, side)

#----------------------------------------------------------------------------------------------------------------------------------------------------

from roblib3 import *

def mark_all(r):
    rss = RobStepSave(r)
    steps_toangle(rss, "sw")

    r.mark()
    rsm = RobStepMark(r)
    from_sw_bypass(rsm)

    steps_toangle(r, "sw")
    steps(r, rss.get_path())