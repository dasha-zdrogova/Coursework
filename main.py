import random
import numpy as np
import time
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from matplotlib import pyplot as plt
import os

def generateData (numberItemsInClass):
    data = []
    for classNum in range(2):
        # Выбираем две случайные точки, которые станут центром для каждого класса
        centerX, centerY = random.random()*50.0, random.random()*50.0

        # Выбираем для каждого узла класса координаты
        # Чтобы точки одного класса находились близко друг к другу,
        # генерируем их координаты с помощью Гауссового распределения
        for rowNum in range(numberItemsInClass):
            data.append([ [random.gauss(centerX,5), random.gauss(centerY,5)], classNum ])
    return data

nItemsInClass = 100
df = generateData(nItemsInClass)
X = [df[i][0] for i in range(len(df))]
Y = [df[i][1] for i in range(len(df))]

first_set = True
second_set = True
reserve = []
with open("test_data.txt", "w") as file:
    file.write(str(2*len(X)) + "\n")
    for i in range(len(X)):

        if first_set:
            if Y[i] == 0:
                file.write(str(X[i][0]) + " " + str(X[i][1]) + " " + str(Y[i]) + "\n")
                first_set = False
                continue
            else: reserve.append([X[i], Y[i]]); continue
        if second_set:
            if Y[i] == 1:
                file.write(str(X[i][0]) + " " + str(X[i][1]) + " " + str(Y[i]) + "\n")
                second_set = False
                continue
            else: reserve.append([X[i], Y[i]]); continue
        else:    
            file.write(str(X[i][0]) + " " + str(X[i][1]) + " " + str(Y[i]) + "\n")

    for i in range(len(reserve)):
        file.write(str(reserve[i][0][0]) + " " + str(reserve[i][0][1]) + " " + str(reserve[i][1]) + "\n")

with open("test_data.txt", "a") as file:
    for i in range(len(X)):
        file.write(str(X[i][0]) + " " + str(X[i][1]) + " " + str(Y[i]) + "\n")

os.system("algorithm.exe")

with open("answer.txt", "r") as file:
    tmp = file.readline().strip()
    if tmp == "-1":
        plt.scatter([X[i][0] for i in range(len(X))],
            [X[i][1] for i in range(len(X))],
            c = [Y[i] for i in range(len(Y))],
            s = 7)
        plt.title("Множества пересекаются")
    else:
        a = float(tmp.strip())
        b = float(file.readline().strip())

        plt.scatter([X[i][0] for i in range(len(X))],
                    [X[i][1] for i in range(len(X))],
                    c = [Y[i] for i in range(len(Y))],
                    s = 7)

        x = np.arange(-100, 100, 0.1)
        plt.plot(x, x*a + b)
        plt.title("Нашлась разделяющая прямая")

plt.show()