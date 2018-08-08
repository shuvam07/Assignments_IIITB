def one():
    d={
        'cse':["ML","DS/ALGO",],
        'ece':["Digital VLSI"]
    }
    return d
 
def two():
    d={
        'cse':["Network","Software System"],
        'ece':["Analog VLSI"]
    }
    return d
    
def three():
    d={
        'cse':["Data Science"],
        'ece':["System Software"]
    }
    return d
    
def four():
    d={
        'cse':["Signal Processing"],
        'ece':["Networking and Communication"]
    }
    return d

def five():
    d={
        'cse':["Theory and Systems"],
        'ece':["Embedded Systems"]
    }
    return d
 
switcher = {
        1: one,
        2: two,
        3: three,
        4: four,
        5: five
    }

def get_course(arg):
    func = switcher.get(arg, "nothing")
    return func()


year = input()
d = get_course(year)
spec = raw_input()
lists = d[spec]
for course in lists:
    print course

