import statslib as sl
import scipy.stats as ss
import numpy as np
print(sl.rnorm(0, 1))
print(sl.rnorm(0, 1, 5))
print(sl.rnorm(0, 1, (3, 3)))

x = np.linspace(-3, 3, 100)
x2 = np.linspace(0.001, 0.999, 100)
dists = [[sl.dnorm, ss.norm.pdf, [x, 0, 1]],
         [sl.pnorm, ss.norm.cdf, [x, 0, 1]],
         [sl.qnorm, ss.norm.ppf, [x2, 0, 1]]]

for d in dists:
    print(np.allclose(d[0](*d[2]), d[1](*d[2])))
