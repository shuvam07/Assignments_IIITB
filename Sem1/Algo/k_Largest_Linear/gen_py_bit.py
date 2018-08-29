import random
f = open("data.txt","w");
for x in xrange(10000):
  f.write(str(random.randint(0,100000))+" ")

