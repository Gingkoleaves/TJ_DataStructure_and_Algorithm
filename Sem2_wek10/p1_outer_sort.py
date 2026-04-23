import time
from random import randint
import random
import matplotlib.pyplot as plt
import heapq

class Student:
    def __init__(self, num, name,total_score,math_score, english_score, chinese_score):
        self.num = num
        self.name = name
        self.total_score = total_score
        self.math_score = math_score
        self.english_score = english_score
        self.chinese_score = chinese_score

    def __gt__(self, other):
        if(self.total_score != other.total_score):
            return self.total_score > other.total_score
        elif(self.chinese_score != other.chinese_score):
            return self.chinese_score > other.chinese_score
        elif(self.math_score != other.math_score):
            return self.math_score > other.math_score
        elif(self.english_score != other.english_score):
            return self.english_score > other.english_score
        else:
            return self.num > other.num

    def __repr__(self):
        return f"Student({self.num}, {self.name}, {self.total_score}, {self.math_score}, {self.english_score}, {self.chinese_score})"

def find_top_m_students(filename, m):
    heap = []
    with open(filename, "r") as f:
        for line in f:
            num, name, total, math, eng, chi = line.strip().split()
            stu = Student(int(num), name, int(total), int(math), int(eng), int(chi))
            if len(heap) < m:
                heapq.heappush(heap, stu)
            else:
                if stu > heap[0]:
                    heapq.heapreplace(heap, stu)
    # 按降序输出
    return sorted(heap, reverse=True)


N=[50000,100000,150000]  # Number of students
m=100

for n in N:
    # Generate random student data
    with open("students.txt", "w") as f:
        for i in range(1, n+1):
            num = i
            name = f"Student{i}"
            total_score = 0
            math_score = 0
            english_score = 0
            chinese_score = 0

            # Generate random scores for each subject
            math_score = random.randint(0, 150)
            english_score = random.randint(0, 150)
            chinese_score = random.randint(0, 150)

            # Calculate total score
            total_score = math_score + english_score + chinese_score

            # Write to file in the specified format
            f.write(f"{num} {name} {total_score} {math_score} {english_score} {chinese_score}\n")

    top_students=find_top_m_students("students.txt", m)
    with open("top_students.txt", "w") as f:
        for student in top_students:
            f.write(f"{student.num} {student.name} {student.total_score} {student.math_score} {student.english_score} {student.chinese_score}\n")


    print("\n")
