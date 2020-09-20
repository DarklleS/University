class Flag:
    def __init__ (self, val):
        self._val = val
    def inv_flag (self):
        self._val = not self._val
    def get_flag (self):
        return self._val

class Counter:
    def __init__ (self, start = 0):
        self._count = start 
    def plus (self, delta = 1):
        self._count+=delta
    def get_count (self):
        return self._count

class Coords:
    def __init__ (self, x, y):
        self._x = x 
        self._y = y
    def step (self, side):
        assert (side in "nows")
        if side == ("o"):
            self._x += 1
        elif side == "w":
            self._x -= 1
        elif side == "n":
            self.y += 1
        elif side == "s":
            self._y -= 1

class OrdinaryRob:
    def __init__(self, r):
        self._rob=r
    def step(self, side):
        self._rob.step(side)
    def is_bord(self, side):
        return self._rob.is_bord(side)
    def mark(self):
        self._rob.mark()
    def is_mark(self):
        return self._rob.is_mark()  
    def get_tmpr(self):
        return self._rob.get_tmpr()

class RobStepMark (OrdinaryRob):
        def step(self, side):
            self.step(side)
            self.mark()

class RobStepCounter(OrdinaryRob,Counter):
        def __init__(self, r):
            super(OrdinaryRob,self).__init__(r)
            super(Counter, self).__init__()
        def step(self, side):
             self.step(side)
             self.plus()

r=Robot()

rsc = RobStepCounter(r)

steps_tolim(rsc, "o")

n = rsc.get_count()

