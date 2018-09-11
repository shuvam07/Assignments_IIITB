f = open("dec_data.txt","r");
s = f.read();
f = open("data2.txt","w");
f.write(bin(int(s)));
