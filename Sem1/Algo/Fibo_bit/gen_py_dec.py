import random
f = open("dec_data.txt","w");
for x in range(1000):
  f.write(str(random.randint(0,9)))

