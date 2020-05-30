def main():
    amount = get_amount()
    print(change(amount * 100))


def change(cents):
    return round(cents // 25 + (cents % 25) // 10 + ((cents % 25) % 10) // 5 + ((cents % 25) % 10) % 5)
    
    
def get_amount():
    while True:                            
        try:
            n = float(input("Change owed: "))         
            if n >= 0:             
                break                            
        except:
            print("INVALİD")
    return n     
    

main()
