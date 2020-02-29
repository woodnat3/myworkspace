# project euler challenge 2

total = 2
go = True
num1 = 1
num2 = 2
while go:
    temp = num2
    num2 = num1 + num2
    num1 = temp
    if num2 < 4000000:
        if num2 % 2 == 0:
            total += num2
    else:
        go = False
print(total)
    