import torch
from torch.utils.cpp_extension import load
ext = load(name='ext', sources=['src/export.cpp'], extra_cflags=['-O3'], verbose=True)
print(type(1.1))
print(ext.debug(1.1))
t = torch.scalar_tensor(1.1)
print(type(t))
print(ext.debug(t))
