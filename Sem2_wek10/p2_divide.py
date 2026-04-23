import random
import time
import matplotlib.pyplot as plt
import numpy as np

# 大根堆，维护最小的k个元素
class k_min_heap:
    def __init__(self, k):
        self.k = k
        self.heap = []
    
    def insert(self, value):
        if len(self.heap) < self.k:
            self.heap.append(value)
            self._heapify_up(len(self.heap) - 1)
        elif value < self.heap[0]:
            self.heap[0] = value
            self._heapify_down(0)    

    def _heapify_up(self, index):
        while index > 0:
            parent = (index - 1) // 2
            if self.heap[index] > self.heap[parent]:  # 大顶堆
                self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
                index = parent
            else:
                break

    def _heapify_down(self, index):
        size = len(self.heap)
        while True:
            largest = index
            left = 2 * index + 1
            right = 2 * index + 2
            if left < size and self.heap[left] > self.heap[largest]:
                largest = left
            if right < size and self.heap[right] > self.heap[largest]:
                largest = right
            if largest != index:
                self.heap[index], self.heap[largest] = self.heap[largest], self.heap[index]
                index = largest
            else:
                break
                
    def get_k_min(self,array):
        for i in range(len(array)):
            self.insert(array[i])
        return self.heap[0]


def randomized_partition(arr, low, high):
    # 随机选择主元并与最后一个元素交换
    pivot_idx = random.randint(low, high)
    arr[pivot_idx], arr[high] = arr[high], arr[pivot_idx]
    pivot = arr[high]
    i = low - 1    
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i + 1

def randomized_select(arr, low, high, k):
    if low == high:
        return arr[low]    
    pivot_idx = randomized_partition(arr, low, high)
    rank = pivot_idx - low + 1    
    if k == rank:
        return arr[pivot_idx]
    elif k < rank:
        return randomized_select(arr, low, pivot_idx-1, k)
    else:
        return randomized_select(arr, pivot_idx+1, high, k-rank)
    
def median_of_medians_select(arr, k):
    if len(arr) <= 5:
        return sorted(arr)[k-1]
    
    groups = [arr[i:i+5] for i in range(0, len(arr), 5)]    
    medians = [sorted(group)[len(group)//2] for group in groups]    
    pivot = median_of_medians_select(medians, len(medians)//2 + 1)

    left = [x for x in arr if x < pivot]
    right = [x for x in arr if x > pivot]
    pivots = [x for x in arr if x == pivot]
    
    if k <= len(left):
        return median_of_medians_select(left, k)
    elif k <= len(left) + len(pivots):
        return pivot
    else:
        return median_of_medians_select(right, k - len(left) - len(pivots))


# 测试代码
array=[]
time_cost=[]

N=[100,1000,10000,100000]
for n in N:
    K=[n//1000,n//500,n//200,n//100,n//50,n//10,n//5,n//3,n//2]
    
    for i in range(0,len(K)):
        if K[i] == 0:
            K[i] = 1

    for k in K:
        array.clear()
        # print(f"随机选择第{k}小元素\n")
        for i in range(1, n+1):
            array.append(random.randint(0, 1000))

        # print("原始数组:", array)

        o1=k_min_heap(k)
        start1=time.time()
        elem1=o1.get_k_min(array)
        end1=time.time()
        time_cost.append(end1-start1)
        # print(f"基于堆选择第{k}小元素：",elem1)
        
        start2=time.time()
        elem2=randomized_select(array, 0, len(array)-1, k)
        end2=time.time()
        time_cost.append(end2-start2)
        # print(f"基于随机选择第{k}小元素：",elem2)

        start3=time.time()
        elem3=median_of_medians_select(array, k)
        end3=time.time()
        time_cost.append(end3-start3)
        # print(f"基于中位数选择第{k}小元素：",elem3)

time_cost = np.array(time_cost).reshape(len(N), len(K)*3)

fig, axes = plt.subplots(1, 4, figsize=(18, 5))  # 一行三列

for i in range(len(N)):
    n=N[i]
    K=[n//1000,n//500,n//200,n//100,n//50,n//10,n//5,n//3,n//2]
    heap_time = time_cost[i][0::3]
    rand_time = time_cost[i][1::3]
    mom_time = time_cost[i][2::3]
    axes[i].plot(K, heap_time, label="Heap",marker='o')
    axes[i].plot(K, rand_time, label="Random",marker='o')
    axes[i].plot(K, mom_time, label="Median",marker='o')
    axes[i].set_xlabel('K')
    axes[i].set_ylabel('Time (seconds)')
    axes[i].set_title(f'N={N[i]}')
    axes[i].legend(loc='upper left')

plt.tight_layout()
plt.show()