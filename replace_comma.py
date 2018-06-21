fo = open("hybrid_map.txt",)
writing = open("in.txt","w")



stri = fo.read();
array = []
array = stri.split(",")

for i in range(len(array)-1):
	array[i] = array[i].strip()
	array[i] = int(array[i])

array[len(array)-1]=0	

for i in range(len(array)):
	if(i%501==0):
		print("\n")
	writing.write(str(array[i])+" ")

print (array)
fo.close()
writing.close	
