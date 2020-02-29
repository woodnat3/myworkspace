# project euler challenge 3

largest = 0
prime = True
num = 600851475143
i = 3

while i < num**(1/2):
    #print(i)
    x = 3
    if num % i == 0:
        while x < i**(1/2):
            if i % x == 0:
                prime = False
            x += 1
        if prime:
            largest = i
    i += 1
print(largest)