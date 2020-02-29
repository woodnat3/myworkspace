# project euler challenge 4

largest = 0
for num1 in range(100, 1000):
    for num2 in range(100, 1000):
        x = num1 * num2
        x = str(x)
        reverse = x[::-1]
        if reverse == x:
            if int(x) > largest:
                largest = int(x)
print(largest)