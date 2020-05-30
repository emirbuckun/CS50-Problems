def main():
    number = get_number()
    check_validity(number)


def check_validity(ccn):
    span = lenght(ccn)
    if ((checklenght(span)) == 1 or (checksum(ccn, span)) == 1):
        print("INVALİD")
        return
    
    card_brand(ccn)
   
    
def lenght(n):
    span = 0
    while n > 0:
        span += 1
        n /= 10
    return span
    
    
def checklenght(span):
    if (span == 13 or span == 15 or span == 16):
        return True
    return False
    
    
def checksum(ccn, span):
    total = 0
    for i in range(span):
        if (i % 2 == 0):
            total += (ccn % 10)
            ccn /= 10
        else:
            digit = (2 * (ccn % 10))
            total += (digit / 10 + digit % 10)
    if (total % 10 == 0):
        return True
    return False
    
    
def card_brand(ccn):
    if ((ccn >= 340000000000000 and ccn < 350000000000000) or (ccn >= 370000000000000 and ccn < 380000000000000)):
        print("AMEX")
    elif ((ccn >= 5100000000000000 and ccn < 5600000000000000)):
        print("MASTERCARD")
    elif ((ccn >= 4000000000000000 and ccn < 5000000000000000) or (ccn >= 4000000000000 and ccn < 5000000000000)):
        print("VISA")
    else:
        print("INVALID")


def get_number():
    while True:
        try:
            n = int(input("Number: "))
            if n >= 0:
                break
        except:
            print("INVALID")
    return n


main()
