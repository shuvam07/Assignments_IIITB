a = 10
print (type(a))  # type is int 

b = 4
print (type(b))  # type is int

c = 3.4
print (type(c))  # type is float

d = a / 10
print (type(d))  # type is int (int / int is int)

e = b * c
print (type(e))  # type is float(int * float = float)

a = a * e
print (type(a))  # type is float(same as above)

s = "IIITB"
print (type(s))  # type is string

t = a + s
print (type(t))  # unsupported operand type(s) for +: 'float' and 'str (Need to type cast float to string to add)
