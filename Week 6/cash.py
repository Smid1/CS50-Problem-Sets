from cs50 import get_float

count = 0

while True:
    change = get_float("Change: ")
    if (change > 0):
        break

# Change is being rounded after each subtraction due to floating point problems
while change > 0:
    if (change >= 0.25):
        change -= 0.25
        change = round(change, 2)
    elif (change >= 0.1):
        change -= 0.10
        change = round(change, 2)
    elif (change >= 0.05):
        change -= 0.05
        change = round(change, 2)
    else:
        change -= 0.01
        change = round(change, 2)

    count += 1

print(count)
