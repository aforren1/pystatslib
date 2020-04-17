import statslib as sl
import numpy as np
import scipy.stats as ss

seed = sl.Engine(1)

# dnorm
x = 1
x_vec = [1,2,3,4,5]
mu = 0
sigma = 1

print(np.isclose(sl.dnorm(x, mu, sigma, False), ss.norm.pdf(x, mu, sigma)))
print(np.isclose(sl.dnorm(x, mu, sigma, True), ss.norm.logpdf(x, mu, sigma)))


print(np.isclose(sl.dnorm(x_vec, mu, sigma, False).sum(), 
                 ss.norm.pdf(x_vec, mu, sigma).sum()))
print(np.isclose(sl.dnorm(x_vec, mu, sigma, True).sum(), 
                 ss.norm.logpdf(x_vec, mu, sigma).sum()))
