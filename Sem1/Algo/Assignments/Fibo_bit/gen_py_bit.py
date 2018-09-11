import random
f = open("data.txt","w");
for x in range(10000000):
  f.write(str(random.randint(0,1)))

