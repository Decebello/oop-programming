import numpy as np
import matplotlib.pyplot as plt

n_values = [1000, 5000, 10000, 50000, 100000, 500000, 1000000]
times    = [0.001, 0.002, 0.003, 0.016, 0.028, 0.187, 0.426]

n_predict = 2_000_000
c         = times[-1] / n_values[-1] ** 2
t_predict = c * n_predict ** 2

n_curve = np.geomspace(n_values[0], n_predict, 200)
t_curve = c * n_curve ** 2

plt.figure(figsize=(12, 8))

plt.plot(n_curve,   t_curve,   'r-',  linewidth=2,  alpha=0.6, label=r'$f(n) = O(n^2)$')
plt.plot(n_values,  times,     'bo-', markersize=8,            label='Реальные замеры')
plt.plot(n_predict, t_predict, 'rs',  markersize=10,
         label=f'Прогноз (N=2M): {t_predict:.1f}s')

for n, t in zip(n_values, times):
    plt.text(n, t * 1.6, f'{t}s', color='blue',
             ha='center', fontsize=9, fontweight='bold')

plt.text(n_predict, t_predict * 1.6, f'{t_predict:.1f}s',
         color='red', ha='center', fontsize=10, fontweight='bold')

plt.xscale('log')
plt.yscale('log')
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.xticks(n_values + [n_predict], [str(v) for v in n_values + [n_predict]], rotation=45)
plt.title('Анализ сложности алгоритма Иосифа (LineList)', fontsize=14)
plt.xlabel('Количество человек (N)', fontsize=12)
plt.ylabel('Время выполнения (сек)', fontsize=12)
plt.legend()
plt.tight_layout()
plt.show()
