
# coding: utf-8

# In[2]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from pandas import *


# In[3]:


x = np.random.randint(1,100,10)
a = np.array(x)
s = pd.Series(a,dtype=object)
print(s)
print(s.values)


# In[4]:


s = pd.Series(a,index = np.random.randint(400,500,10))
print(s)


# In[5]:


dictionary = {'h':123,'g':392,'c':980}
print(pd.Series(dictionary))


# In[6]:


pop_dict = {'Uttar Pradesh': 38332521,'Karnataka': 26448193,'Haryana': 19651127}
pop = pd.Series(pop_dict)
print(pop['Karnataka'])
print(pop[2])


# In[7]:


s = pd.Series(range(10), index = [x for x in 'abcdefghij'])
print(s[:3])
print(s[:'c'])

# Retrieve the last element
print(s[-1:])

# Accessing everything but the last element
print(s[:-1])


# In[8]:


data = pd.read_csv('Iris.csv')
data.describe()
data.info()
data.dropna().head()


# In[9]:


cols = list(data.columns)
print(cols)


# In[26]:


n = 10
first_n = data[:n]
print(first_n)


# In[27]:


data.iloc[n-1]


# In[28]:


data.iloc[2:10, 1:3]


# In[29]:


data['newCol'] = 0
print(data.head())
# Drop the new column
data.drop('newCol', axis='columns', inplace=True)
data.head()


# In[31]:


sepal_lengths = data['SepalLengthCm'] 
mean = np.mean(sepal_lengths)


# In[32]:


do = lambda x : x - mean

mean_sepal = data['SepalLengthCm'].apply(do)
print(mean_sepal.head())


# In[33]:


data.sort_values(by=['PetalLengthCm'], ascending=True, inplace=False).head()


# In[34]:


data['Species'].value_counts()


# In[35]:


data['Species'].value_counts().cumsum()


# In[36]:


data.drop_duplicates().head()


# In[37]:


data.drop('PetalLengthCm', axis='columns', inplace=False).head()


# In[38]:


data.pivot_table(values='SepalLengthCm', index='Species', aggfunc=np.sum)


# In[39]:


data.pivot_table(values='SepalLengthCm', index='Species', aggfunc=np.mean)


# In[9]:


ax = data[data.Species=='Iris-setosa'].plot.scatter(x='SepalLengthCm', y='SepalWidthCm', color='red', label='Setosa')
data[data.Species=='Iris-versicolor'].plot.scatter(x='SepalLengthCm', y='SepalWidthCm', color='green', label='Versicolor', ax = ax)
data[data.Species=='Iris-virginica'].plot.scatter(x='SepalLengthCm', y='SepalWidthCm', color='blue', label='Virginica', ax = ax)

ax.set_title("Scatter plot between sepal length and sepal width")
plt.show()


# In[12]:


_ = plt.hist(data[data.Species=='Iris-setosa'].SepalLengthCm)
_ = plt.hist(data[data.Species=='Iris-versicolor'].SepalLengthCm)
_ = plt.hist(data[data.Species=='Iris-virginica'].SepalLengthCm)
plt.xlabel("SepalLengthCm")
plt.ylabel("Number of Instances")
plt.title("Species vs SepalLengthCm")
plt.show()


# In[13]:


_ = plt.hist(data[data.Species=='Iris-setosa'].SepalWidthCm)
_ = plt.hist(data[data.Species=='Iris-versicolor'].SepalWidthCm)
_ = plt.hist(data[data.Species=='Iris-virginica'].SepalWidthCm)
plt.xlabel("SepalWidthCm")
plt.ylabel("Number of Instances")
plt.title("Species vs SepalWidthCm")
plt.show()


# In[15]:


_ = plt.hist(data[data.Species=='Iris-setosa'].PetalLengthCm)
_ = plt.hist(data[data.Species=='Iris-versicolor'].PetalLengthCm)
_ = plt.hist(data[data.Species=='Iris-virginica'].PetalLengthCm)
plt.xlabel("PetalLengthCm")
plt.ylabel("Number of Instances")
plt.title("Species vs PetalLengthCm")
plt.show()


# In[14]:


_ = plt.hist(data[data.Species=='Iris-setosa'].PetalWidthCm)
_ = plt.hist(data[data.Species=='Iris-versicolor'].PetalWidthCm)
_ = plt.hist(data[data.Species=='Iris-virginica'].PetalWidthCm)
plt.xlabel("PetalWidthCm")
plt.ylabel("Number of Instances")
plt.title("Species vs PetalWidthCm")
plt.show()


# In[88]:


for col in data.columns[1:]:
    print(col)
    print(data[col].unique())


# In[95]:


df = pd.DataFrame(data)
for col in data.columns[1:]:
    print(col)
    for val in data[col].unique():
        print(df.loc[df[col]==val])


# In[103]:


df['sum'] = df['SepalLengthCm']+df['SepalWidthCm']+df['PetalLengthCm']+df['PetalWidthCm']
df.head()


# In[106]:


df.to_csv("DataFrameCSV", sep='\t')

