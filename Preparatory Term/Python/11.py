def one():
    return "ML,Algorithm,Java,Python"
 
def two():
    return "Network,Software System""
 
def three():
    return "Data Science"

def four():
    return "Networking"

def five():
    return "Signal Processing"
 
switcher = {
        1: one,
        2: two,
        3: three,
        4: four,
        5: five
    }
 
 
def get_course(argument):
    func = switcher.get(argument, "nothing")
    return func()

get_course(1)
