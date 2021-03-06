import numpy as np 
import struct
import matplotlib.pyplot as plt
import matplotlib

hlist = []
alist = []
tots = []
constants = []
with open("outputMC.bin", "rb") as f:
	j=0
	while True:
		head = f.read(8)
		if head:
			j+= 1
			h = struct.unpack('ii',head)
			hours = h[0]
			ssize = h[1]
			c = f.read(ssize)
			constants.append(c)
			dur = hours*60*60
			h = np.ones(dur)
			a = np.ones(dur)
			print(j,dur)
			for i in range(dur):
				dat = f.read(8)
				d = struct.unpack('fi',dat)
				h[i] = d[0]
				a[i] = d[0]
			tot = np.sum(np.abs(np.diff(a)))
			alist.append(np.diff(a))
			tots.append(tot)
			hlist.append(h)
			
		else:
			break

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 5}

matplotlib.rc('font', **font)

for i in range(20):
	plt.subplot(5,5,i+1)
	plt.hist(hlist[i],100)
	plt.title("{0:.2E}, {1:.2E}, {2:.2E}".format(tots[i],struct.unpack('f',constants[i][4:8])[0],np.std(hlist[i])))

plt.tight_layout()
plt.show()