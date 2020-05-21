from functools import partial
import numpy as np
import scipy.stats as ss
import statslib as sl

def_x = np.linspace(-5, 5, num=100)

tests = [{'norm': {'stats': sl.dnorm, 'x': def_x}}]

#for t in tests:
t = tests[0]
name = list(t.keys())[0]
sci = getattr(ss, name)
sci_pdf = sci.pdf
sci_lpdf = sci.logpdf
sl_pdf = t[name]['stats']
sl_lpdf = partial(sl_pdf, log_form=True)
x = t[name]['x']

