from cs50 import get_int

number = get_int("Number: ")
sum = 0

aux = number
while aux >= 100:
    aux /= 10

firstDigits = int(aux)

while number > 0:
    # Takes the last digit and adds it to the sum
    sum += number % 10
    number = int(number / 10)

    # Takes the second to last (now last) digit and add to the sum
    digit = (number % 10) * 2
    if digit >= 10: # If digit * 2 is greater or equal to 10
        sum += digit % 10
        digit = int(digit / 10)
        sum += digit
    else:
        sum += digit
    number = int(number / 10)

if sum % 10 != 0:
    firstDigits = 0

if firstDigits in [34, 37]:
    print("AMEX")
elif firstDigits in range(50, 56):
    print("MASTERCARD")
elif firstDigits in range(40, 49):
    print("VISA")
else:
    print("INVALID")
