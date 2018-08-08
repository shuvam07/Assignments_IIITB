op = raw_input("Enter a operation add(+) mult(*) or avg(/)\n")[0]
a = input()
b = input()

if (op == '+'):
    print (a+b)
elif (op == '*'):
    print (a*b)
elif (op == '/'):
    print (float(a)+float(b))/2
