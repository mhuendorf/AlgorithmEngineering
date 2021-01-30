import os
path = '/home/thomas/AE/firstComparison/countries'
files = os.listdir(path)

for file in files:
    os.rename(os.path.join(path, file), os.path.join(path, file+'.txt'))