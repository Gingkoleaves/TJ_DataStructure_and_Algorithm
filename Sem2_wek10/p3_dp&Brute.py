import random
import time
import matplotlib.pyplot as plt
import numpy as np


def dp(cards):
    n = len(cards)
    total = sum(cards)
    target = total // 2
    
    
    dp= [0]*(target+1)
    path = [[] for _ in range(target + 1)]


    dp[0] = 1
    path[0] = []

    for i in range(n):
        for j in range(target, cards[i]-1, -1):
            if dp[j - cards[i]] > 0 and dp[j] == 0:
                dp[j] = 1
                path[j] = path[j - cards[i]] + [i]

    
    for i in range(target, -1, -1):
        if dp[i] > 0:
            return i,path[i]
        
def brute_force(cards):
    n = len(cards)
    ans_total=0
    path=[]

    for i in range((1 << n)-1):
        total = 0
        for j in range(n):
            if (i >> j) & 1:
                total += cards[j]

        if total > sum(cards)//2:
            total=sum(cards) - total 
        
        if total > ans_total:
            ans_total = total
            path = []
            for j in range(n):
                if (i >> j) & 1:
                    path.append(j)

    return ans_total, path


N=[5,10,15,18,20,21]
cards=[]
DP_time=[]
Brute_time=[]

for n in N:
    cards.clear()
    for i in range(n):
        cards.append(random.randint(1, 100))

    start1 = time.time()
    res1,path1=dp(cards)
    end1 = time.time()
    DP_time.append(end1 - start1)

    start2 = time.time()
    res2,path2=brute_force(cards)
    end2 = time.time()
    Brute_time.append(end2 - start2)

    # print("DP Result: ", res1, "Path: ", path1, "Time: ", end1 - start1)
    # print("Brute Force Result: ", res2, "Path: ", path2, "Time: ", end2 - start2)

plt.plot(N, DP_time, label='DP Time')
plt.plot(N, Brute_time, label='Brute Force Time')
plt.xlabel('Number of Cards')
plt.ylabel('Time (seconds)')
plt.title('Time Complexity of DP vs Brute Force')
plt.legend()
plt.show()

plt.savefig('time_complexity.png')
plt.clf()