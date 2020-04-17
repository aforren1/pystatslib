import statslib as sl
import numpy as np
import scipy.stats as ss

seed = sl.Engine(1)

# dnorm
x = 1
x_vec = [1,2,3,4,5]
mu = 0
sigma = 1

sl.dnorm(x, mu, sigma)