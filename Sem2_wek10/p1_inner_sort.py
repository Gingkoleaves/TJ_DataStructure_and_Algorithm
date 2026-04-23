import time
from random import randint
import random
import matplotlib.pyplot as plt

class student:
    def __init__(self, num, name,total_score,math_score, english_score, chinese_score):
        self.num = num
        self.name = name
        self.total_score = total_score
        self.math_score = math_score
        self.english_score = english_score
        self.chinese_score = chinese_score

    def __lt__(self, other):
        if(self.total_score != other.total_score):
            return self.total_score > other.total_score
        elif(self.chinese_score != other.chinese_score):
            return self.chinese_score > other.chinese_score
        elif(self.math_score != other.math_score):
            return self.math_score > other.math_score
        elif(self.english_score != other.english_score):
            return self.english_score > other.english_score
        else:
            return self.num < other.num

    def __repr__(self):
        return f"Student({self.num}, {self.name}, {self.total_score}, {self.math_score}, {self.english_score}, {self.chinese_score})"

def partition(students, low, high):
    pivot = students[high]
    i = low - 1
    for j in range(low, high):
        if students[j] < pivot:
            i += 1
            students[i], students[j] = students[j], students[i]
    students[i + 1], students[high] = students[high], students[i + 1]
    return i + 1

def quick_sort(students, low, high):
    if low < high:
        pi = partition(students, low, high)
        quick_sort(students, low, pi - 1)
        quick_sort(students, pi + 1, high)

def bubble_sort(students):
    n = len(students)
    for i in range(n):
        for j in range(0, n-i-1):
            if students[j] > students[j+1]:
                students[j], students[j+1] = students[j+1], students[j]

N=[50,250,500,2500,5000,25000,50000]  # Number of students
quick_sort_time = []
bubble_sort_time = []

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

    students = []

    with open("students.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            parts = line.strip().split()
            num = int(parts[0])
            name = parts[1]
            total_score = int(parts[2])
            math_score = int(parts[3])
            english_score = int(parts[4])
            chinese_score = int(parts[5])
            students.append(student(num, name, total_score, math_score, english_score, chinese_score))

    quick_sort_start_time = time.time()
    sorted_students = quick_sort(students, 0, len(students) - 1)
    quick_sort_end_time = time.time()
    quick_sort_time.append(quick_sort_end_time - quick_sort_start_time)

    bubble_sort_start_time = time.time()
    bubble_sort(students)
    bubble_sort_end_time = time.time()
    bubble_sort_time.append(bubble_sort_end_time - bubble_sort_start_time)

    
    # with open("sorted_students.txt",w) as out:
    #     for student in students:
    #         out.write(f"{student.num} {student.name} {student.total_score} {student.math_score} {student.english_score} {student.chinese_score}\n")

    
plt.plot(N, quick_sort_time, label='Quick Sort', marker='o')
plt.plot(N, bubble_sort_time, label='Bubble Sort', marker='o')

plt.xlabel('Number of Students')
plt.ylabel('Time (seconds)')

plt.title('Sorting Time Comparison')
plt.legend(loc='upper left')
plt.show()

plt.savefig('sorting_time_comparison.png')
plt.close()