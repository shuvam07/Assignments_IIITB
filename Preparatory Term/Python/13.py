def word_form(number):
    
    ones = ("", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine")
    tens = ("", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety")
    teens = ("ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen")
    levels = ("", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion")

    word = ""
    number = "".join(reversed(str(number)))
    if (len(number) % 3 == 1): 
        number += "0"
    x = 0
    for digit in number:
        if x % 3 == 0:
            word = levels[x / 3] + ", " + word
            n = int(digit)
        elif x % 3 == 1:
            if digit == "1":
                num = teens[n]
            else:
                num = tens[int(digit)]
                if n:
                    if num:
                        num += "-" + ones[n]
                    else:
                        num = ones[n]
            word = num + " " + word
        elif x % 3 == 2:
            if digit != "0":
                word = ones[int(digit)] + " hundred " + word
        x += 1
    return word.strip(", ")
    
n = input()
print word_form(n)
