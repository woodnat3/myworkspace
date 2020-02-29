# project euler challenge 1

total = 0
x = 1000
for i in range(x):
    if i % 3 == 0:
        total += i
    elif i % 5 == 0:
        total += i

print(total)