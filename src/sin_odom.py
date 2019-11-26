import numpy as np
import matplotlib.pyplot as plt

# step
step = 0.1
# create simulation data
amplitude = 0.6; cycle = 1.0
x = np.arange(0, 1.5*np.pi, step)
# y axis offset +1.0
y = amplitude*np.sin(cycle*x) + 1.0
dy = amplitude*cycle*np.cos(cycle*x)
ddy = -amplitude*cycle**2*np.sin(cycle*x)
# show gt trajectory
# plt.plot(x, y, label='gt')
# motion variable
theta = np.arctan(dy)
omega = ddy * 1.0 / (1.0+dy**2)
velocity = np.sqrt(1.0+dy**2)
plt.scatter(x, y, s=1, c='r')
# initial position
init_position_x = x[0]; init_position_y = y[0]
delta_x = np.array([x[i] - x[i-1] for i in xrange(1, len(x))], dtype=float)
delta_x += np.random.normal(0, 0.005)
delta_y = np.array([y[i] - y[i-1] for i in xrange(1, len(y))], dtype=float)
delta_y += np.random.normal(0, 0.005)
# calc trajectory noised
noised_x = np.append(np.array(x[0]), delta_x)
noised_y = np.append(np.array(y[0]), delta_y)
for i in xrange(1, len(noised_x)):
    noised_x[i] += noised_x[i-1]
    noised_y[i] += noised_y[i-1]
# show noised trajectory
plt.scatter(noised_x, noised_y, s=1, c='g')

# data size
print ('data size: {}'.format(len(x)))

plt.legend()
plt.show()
