
import random as rand
import time
import numpy

rand.seed(time.time())

#formula y = mx + b

slope = -2
intercept = 3

f = open("test2.csv", "w")

for i in range(5, 50 + 1):
    y_value = slope*i + intercept
    y_value = y_value + numpy.random.normal(0, 25)
  
    f.write(f"{i} \t {y_value}\n")